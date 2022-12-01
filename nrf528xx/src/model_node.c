#include <zephyr/bluetooth/bluetooth.h>
#include <bluetooth/mesh/models.h>
#include <dk_buttons_and_leds.h>
#include "model_node.h"

/*** initialising server a.k.a led*/

static void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx * ctx,
                    const struct bt_mesh_onoff_set *set,
                    struct bt_mesh_onoff_status *rsp);
static void led_get(struct bt_mesh_onoff_srv *srv, 
                    struct bt_mesh_msg_ctx * ctx,
                    struct bt_mesh_onoff_status *rsp);
static const struct bt_mesh_onoff_srv_handlers onoff_handlers_srv = {
	.set = led_set,
	.get = led_get,
};

struct led_ctx {
	struct bt_mesh_onoff_srv srv;
	struct k_work_delayable work;
	uint32_t remaining;
	bool value;
};


static struct led_ctx led_ctx[] = {
#if DT_NODE_EXISTS(DT_ALIAS(led0))
	{ .srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers_srv) },
#endif
#if DT_NODE_EXISTS(DT_ALIAS(led1))
	{ .srv = BT_MESH_ONOFF_SRV_INIT(&onoff_handlers_srv) },
#endif
};

static void led_transition_start(struct led_ctx *led)
{
	int led_idx = led - &led_ctx[0];

	/* As long as the transition is in progress, the onoff
	 * state is "on":
	 */
	dk_set_led(led_idx, true);
	k_work_reschedule(&led->work, K_MSEC(led->remaining));
	led->remaining = 0;
}

static void led_status(struct led_ctx *led, struct bt_mesh_onoff_status *status)
{
	/* Do not include delay in the remaining time. */
	status->remaining_time = led->remaining ? led->remaining :
		k_ticks_to_ms_ceil32(k_work_delayable_remaining_get(&led->work));
	status->target_on_off = led->value;
	/* As long as the transition is in progress, the onoff state is "on": */
	status->present_on_off = led->value || status->remaining_time;
}

static void led_set(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
		    const struct bt_mesh_onoff_set *set,
		    struct bt_mesh_onoff_status *rsp)
{
	struct led_ctx *led = CONTAINER_OF(srv, struct led_ctx, srv);
	int led_idx = led - &led_ctx[0];

	if (set->on_off == led->value) {
		goto respond;
	}

	led->value = set->on_off;
	if (!bt_mesh_model_transition_time(set->transition)) {
		led->remaining = 0;
		dk_set_led(led_idx, set->on_off);
		goto respond;
	}

	led->remaining = set->transition->time;

	if (set->transition->delay) {
		k_work_reschedule(&led->work, K_MSEC(set->transition->delay));
	} else {
		led_transition_start(led);
	}

respond:
	if (rsp) {
		led_status(led, rsp);
	}
}

static void led_get(struct bt_mesh_onoff_srv *srv, struct bt_mesh_msg_ctx *ctx,
		    struct bt_mesh_onoff_status *rsp)
{
	struct led_ctx *led = CONTAINER_OF(srv, struct led_ctx, srv);

	led_status(led, rsp);
}

static void led_work(struct k_work *work)
{
	struct led_ctx *led = CONTAINER_OF(work, struct led_ctx, work.work);
	int led_idx = led - &led_ctx[0];

	if (led->remaining) {
		led_transition_start(led);
	} else {
		dk_set_led(led_idx, led->value);

		/* Publish the new value at the end of the transition */
		struct bt_mesh_onoff_status status;

		led_status(led, &status);
		bt_mesh_onoff_srv_pub(&led->srv, NULL, &status);
	}
}


/*** initialising client a.k.a button*/

/** Context for a light switch*/
struct button {
    /** Current light status of the corresponding server. */
    bool status;
    /** Generic OnOff client instance for this switch. */
    struct bt_mesh_onoff_cli client;
};
/** status handler from client*/
static void status_handler_client( struct bt_mesh_onoff_cli *cli, 
                            struct bt_mesh_msg_ctx *ctx, 
                            const struct bt_mesh_onoff_status *status);
static struct button buttons[] = {
#if DT_NODE_EXISTS(DT_ALIAS(sw0))
	{ .client = BT_MESH_ONOFF_CLI_INIT(&status_handler_client) },
#endif
#if DT_NODE_EXISTS(DT_ALIAS(sw1))
	{ .client = BT_MESH_ONOFF_CLI_INIT(&status_handler_client) },

#endif
};

static void status_handler_client( struct bt_mesh_onoff_cli *cli, 
                            struct bt_mesh_msg_ctx *ctx, 
                            const struct bt_mesh_onoff_status *status)
{
    struct button* button =
        CONTAINER_OF(cli, struct button, client);
    int index = button - &buttons[0];

    button->status = status->present_on_off;
    dk_set_led(index, status->present_on_off);
    	
    printk("Button %d: Received response: %s\n", index + 1,
	    status->present_on_off ? "on" : "off");

}


/** status handler button*/

/** button handler of button state is changed */
static void button_handler_cb(uint32_t pressed, uint32_t changed)
{
    if(!bt_mesh_is_provisioned()){return;}

    for(int i =0; i < ARRAY_SIZE(buttons); i++)
    {
        if(!(pressed & changed & BIT(i))){continue;}


        struct bt_mesh_onoff_set set = {
            .on_off = !buttons[i].status,
        };

        int error;

        if(bt_mesh_model_pub_is_unicast(buttons[i].client.model)){
            error = bt_mesh_onoff_cli_set(&buttons[i].client, NULL, &set, NULL);
        }
        else{
            error = bt_mesh_onoff_cli_set_unack(&buttons[i].client, NULL, &set);
            /** unacked messeges have no response status. set the state immmediately*/
            if(!error){
                buttons[i].status = set.on_off;
                dk_set_led(i,set.on_off);
            }
        }
        if(error){
            printk("onOff %d set failed: %d\n",i+1,error);
        }

    }

}


static struct k_work_delayable attention_blink_work;
static bool attention;

static void attention_blink(struct k_work *work)
{
	static int idx;
	const uint8_t pattern[] = {
#if DT_NODE_EXISTS(DT_ALIAS(sw0))
		BIT(0),
#endif
#if DT_NODE_EXISTS(DT_ALIAS(sw1))
		BIT(1),
#endif
#if DT_NODE_EXISTS(DT_ALIAS(led0))
		BIT(2),
#endif
#if DT_NODE_EXISTS(DT_ALIAS(led1))
		BIT(3),
#endif
	};

	if (attention) {
		dk_set_leds(pattern[idx++ % ARRAY_SIZE(pattern)]);
		k_work_reschedule(&attention_blink_work, K_MSEC(30));
	} else {
		dk_set_leds(DK_NO_LEDS_MSK);
	}
}

static void attention_on(struct bt_mesh_model *mod)
{
	attention = true;
	k_work_reschedule(&attention_blink_work, K_NO_WAIT);
}

static void attention_off(struct bt_mesh_model *mod)
{
	/* Will stop rescheduling blink timer */
	attention = false;
}

static const struct bt_mesh_health_srv_cb health_srv_cb = {
	.attn_on = attention_on,
	.attn_off = attention_off,
};

static struct bt_mesh_health_srv health_srv = {
	.cb = &health_srv_cb,
};

BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

static struct bt_mesh_elem elements[] = {
#if DT_NODE_EXISTS(DT_ALIAS(sw0))
	BT_MESH_ELEM(1,
		     BT_MESH_MODEL_LIST(
			     BT_MESH_MODEL_CFG_SRV,
			     BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
			     BT_MESH_MODEL_ONOFF_CLI(&buttons[0].client)),
		     BT_MESH_MODEL_NONE),
#endif
#if DT_NODE_EXISTS(DT_ALIAS(sw1))
	BT_MESH_ELEM(2,
		     BT_MESH_MODEL_LIST(
			     BT_MESH_MODEL_ONOFF_CLI(&buttons[1].client)),
		     BT_MESH_MODEL_NONE),
#endif
#if DT_NODE_EXISTS(DT_ALIAS(led1))
	BT_MESH_ELEM(
		3, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[0].srv)),
		BT_MESH_MODEL_NONE),
#endif
#if DT_NODE_EXISTS(DT_ALIAS(led2))
	BT_MESH_ELEM(
		4, BT_MESH_MODEL_LIST(BT_MESH_MODEL_ONOFF_SRV(&led_ctx[1].srv)),
		BT_MESH_MODEL_NONE),
#endif
};

static const struct bt_mesh_comp comp ={
    .cid = CONFIG_BT_COMPANY_ID,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};

const struct bt_mesh_comp *model_node_init(void)
{
    static struct button_handler button_handler = {
        .cb = button_handler_cb,
    };

    dk_button_handler_add(&button_handler);
    k_work_init_delayable(&attention_blink_work,attention_blink);

	for (int i = 0; i < ARRAY_SIZE(led_ctx); ++i) {
		k_work_init_delayable(&led_ctx[i].work, led_work);
	}

    return &comp;
}

