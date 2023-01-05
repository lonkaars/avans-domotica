#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** @file protocol.h */

#define CD_SERIAL_START_BYTE 0xff

#include <stdint.h>
#include <stdlib.h>

#include "bin.h"
#include "consts.h"

/** @brief mac address (00:11:22:33:44:55) */
typedef uint8_t cd_mac_addr_t[6];
/** @brief uuid (ffeeddcc-bbaa-9988-7766-554433221100) */
typedef uint8_t cd_uuid_t[16];

/** @brief pub/sub address type */
typedef uint32_t cd_mesh_psub_addr;

/** @brief command opcode (identifies message type) */
typedef uint8_t cd_cmd_opcode_t;
/** @brief command id (identifies messages uniquely) */
typedef uint16_t cd_cmd_id_t;
/** @brief smallest boolean type */
typedef uint8_t cd_cmd_bool_t;

/** @brief cmd handler function signature */
typedef void (cd_cmd_handler_t)(cd_s_bin *data);

/** @brief used for numbering messages */
extern cd_cmd_id_t g_cd_protocol_fresh_message_id;

/** @brief get new message id */
cd_cmd_id_t cd_protocol_fresh_message_id();

#pragma pack(push, 1)

typedef struct {
	cd_cmd_opcode_t opcode; /** @brief cmd opcode */
	cd_cmd_id_t id; /** @brief message id */
} cd_s_cmd_ping;

typedef struct {
	cd_cmd_opcode_t opcode; /** @brief cmd opcode */
	cd_cmd_id_t id; /** @brief message id */
	cd_cmd_bool_t all; /** @brief get all known nodes */
	cd_uuid_t uuid; /** @brief node uuid to get details from, ignored if `all` = `true` */
} cd_s_cmd_get_node;

typedef struct {
	cd_cmd_opcode_t opcode; /** @brief cmd opcode */
	cd_cmd_id_t id; /** @brief message id */
	cd_cmd_bool_t on; /** @brief new led status */
	cd_uuid_t uuid; /** @brief node uuid to set */
} cd_s_cmd_post_led;

typedef enum {
	CD_CMD_LINK_TYPE_TOGGLE = 0x00,
	CD_CMD_LINK_TYPE_TURN_ON = 0x01,
	CD_CMD_LINK_TYPE_TURN_OFF = 0x02,
} cd_e_cmd_link_type;

typedef struct {
	cd_cmd_opcode_t opcode; /** @brief cmd opcode */
	cd_cmd_id_t id; /** @brief message id */
	cd_uuid_t button; /** @brief uuid of button node */
	cd_uuid_t led; /** @brief uuid of led node */
	cd_cmd_bool_t add; /** @brief `true` to create/overwrite link, `false` to remove link */
	cd_e_cmd_link_type type; /** @brief link type */
} cd_s_cmd_post_link;

typedef struct {
	cd_cmd_opcode_t opcode; /** @brief cmd opcode */
	cd_cmd_id_t id; /** @brief message id */
	cd_uuid_t uuid; /** @brief node uuid */
	cd_cmd_bool_t join; /** @brief `true` to join network, `false` to leave network */
} cd_s_cmd_post_net;

/** @brief protocol node */
typedef struct {
	cd_uuid_t uuid;		   /** @brief node network uuid */
	cd_mac_addr_t address; /** @brief node bluetooth mac address */
	uint8_t name_len;	   /** @brief name length in bytes */
	cd_cmd_bool_t light_on;		   /** @brief state of light on node */
	cd_cmd_bool_t provisioned;	   /** @brief whether the node is provisioned into the network */
	cd_mesh_psub_addr button_pub; /** @brief button publish address */
	uint16_t link_count; /** @brief amount of addresses to publish button press to */
	uint16_t remaining_size; /** @brief calculated size of remaining_data for convenience */
	const uint8_t remaining_data[]; /**
									 * @brief remaining data (name and link array)
									 *
									 * this data is stored adjacently in memory
									 * and is cast when reading/writing this
									 * struct
									 * 
									 * 1. char[] name
									 * 2. cd_uuid_t[] light_publish_addresses;
									 */
} cd_s_cmd_node;

typedef struct {
	uint16_t node_count; /** amount of nodes in nodes[] */
	uint16_t remaining_size; /** remaining size (for convenience) */
	cd_s_cmd_node nodes[]; /** nodes adjacent in memory (should be accessed using pointer arithmetic) */
} cd_s_cmd_response_get_node;

typedef struct {
	cd_cmd_opcode_t opcode; /** @brief cmd opcode */
	cd_cmd_id_t id; /** @brief response message id */
	cd_cmd_bool_t error; /** @brief `true` if some error occurred */
	cd_cmd_opcode_t response_type; /** @brief response type, used to cast type of `response_info` */
	cd_cmd_id_t response_id; /** @brief original message id */
	uint16_t response_size; /** @brief size of remaining response */
	uint8_t response_info[]; /** @brief (CAST) remaining response struct, not read if `response_size`=`0` */
} cd_s_cmd_response;

#pragma pack(pop)

/** @brief global handler for complete messages */
void cd_cmd_handle(uint8_t data[CD_SERIAL_READ_BUFFER_SIZE], uint8_t length);
/** @brief calculate message length for any message */
size_t cd_cmd_sizeof(uint8_t data[CD_SERIAL_READ_BUFFER_SIZE], uint8_t length);

/** @brief calculate dynamic size of response message */
size_t cd_cmd_response_sizeof(cd_s_bin* data);

// down here is the garbage manual duplicate code section for constants

#define CD_CMD_COUNT 6
typedef enum {
	CD_CMD_PING = 0x00, /** @brief send ping */
	CD_CMD_GET_NODE = 0x01, /** @brief get node(s) */
	CD_CMD_POST_LED = 0x02, /** @brief set led */
	CD_CMD_POST_LINK = 0x03, /** @brief set/remove link */
	CD_CMD_POST_NET = 0x04, /** @brief (un)register node with network */
	CD_CMD_RESPONSE = 0x05, /** @brief response message */
} cd_e_scmds;

cd_cmd_handler_t cd_cmd_ping,
				 cd_cmd_get_node,
				 cd_cmd_post_led,
				 cd_cmd_post_link,
				 cd_cmd_post_net,
				 cd_cmd_response;

/** @brief constant message sizes, 0 for dynamic size */
static const size_t CD_CMD_HANDLERS_SIZE[CD_CMD_COUNT] = {
	[CD_CMD_PING] = sizeof(cd_s_cmd_ping),
	[CD_CMD_GET_NODE] = sizeof(cd_s_cmd_get_node),
	[CD_CMD_POST_LED] = sizeof(cd_s_cmd_post_led),
	[CD_CMD_POST_LINK] = sizeof(cd_s_cmd_post_link),
	[CD_CMD_POST_NET] = sizeof(cd_s_cmd_post_net),
	[CD_CMD_RESPONSE] = 0,
};

/** @brief constant message sizes, 0 for dynamic size */
static size_t (* const CD_CMD_HANDLERS_SIZEOF[CD_CMD_COUNT])(cd_s_bin*) = {
	[CD_CMD_PING] = NULL,
	[CD_CMD_GET_NODE] = NULL,
	[CD_CMD_POST_LED] = NULL,
	[CD_CMD_POST_LINK] = NULL,
	[CD_CMD_POST_NET] = NULL,
	[CD_CMD_RESPONSE] = &cd_cmd_response_sizeof,
};

/** @brief stores message handlers in array with opcode as index */
static cd_cmd_handler_t* const CD_CMD_HANDLERS[CD_CMD_COUNT] = {
	[CD_CMD_PING] = &cd_cmd_ping,
	[CD_CMD_GET_NODE] = &cd_cmd_get_node,
	[CD_CMD_POST_LED] = &cd_cmd_post_led,
	[CD_CMD_POST_LINK] = &cd_cmd_post_link,
	[CD_CMD_POST_NET] = &cd_cmd_post_net,
	[CD_CMD_RESPONSE] = &cd_cmd_response,
};

#ifdef __cplusplus
}
#endif
