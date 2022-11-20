#include <zephyr/drivers/gpio.h>
#include <zephyr/zephyr.h>

static const struct gpio_dt_spec CD_LED = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

void main() { // NOLINT
	gpio_pin_configure_dt(&CD_LED, GPIO_OUTPUT_ACTIVE);

	while (1) {
		gpio_pin_toggle_dt(&CD_LED);
		k_msleep(500);
	}
}
