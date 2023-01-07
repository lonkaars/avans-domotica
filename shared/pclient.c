#include <string.h>

#include "protocol.h"
#include "pclient.h"
#include "bin.h"

#ifdef __cplusplus
extern "C" {
#endif

cd_s_bin* cd_cmd_gen_ping() {
	CD_CREATE_MSG_BIN(cd_s_cmd_ping, msg, bin);

	msg->opcode = CD_CMD_PING;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());

	return bin;
}

cd_s_bin* cd_cmd_gen_get_node(bool all, cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_get_node, msg, bin);

	msg->opcode = CD_CMD_GET_NODE;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->all = all;
	if (uuid != NULL) memcpy(msg->uuid, uuid, sizeof(cd_uuid_t));
	else memset(msg->uuid, 0, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_led(bool on, cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_led, msg, bin);

	msg->opcode = CD_CMD_POST_LED;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->on = on;
	memcpy(msg->uuid, uuid, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_link_add(cd_uuid_t button, cd_uuid_t light, cd_e_cmd_link_type type) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_link, msg, bin);

	msg->opcode = CD_CMD_POST_LINK;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->add = true;
	memcpy(msg->button, button, sizeof(cd_uuid_t));
	memcpy(msg->led, light, sizeof(cd_uuid_t));
	msg->type = type;

	return bin;
}

cd_s_bin* cd_cmd_gen_post_link_rm(cd_uuid_t button, cd_uuid_t light) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_link, msg, bin);

	msg->opcode = CD_CMD_POST_LINK;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->add = false;
	memcpy(msg->button, button, sizeof(cd_uuid_t));
	memcpy(msg->led, light, sizeof(cd_uuid_t));
	msg->type = 0;

	return bin;
}

cd_s_bin* cd_cmd_gen_post_net_add(cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_net, msg, bin);

	msg->opcode = CD_CMD_POST_NET;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->join = true;
	memcpy(msg->uuid, uuid, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_net_rm(cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_net, msg, bin);

	msg->opcode = CD_CMD_POST_NET;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->join = false;
	memcpy(msg->uuid, uuid, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_res_status(cd_e_scmds cmd, cd_cmd_id_t id, bool error) {
	CD_CREATE_MSG_BIN(cd_s_cmd_response, msg, bin);

	msg->opcode = CD_CMD_RESPONSE;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->response_type = cmd;
	msg->response_id = id;
	msg->error = error;
	msg->response_size = 0;

	return bin;
}

cd_s_bin* cd_cmd_res(cd_e_scmds cmd, cd_cmd_id_t id, uint16_t len, uint8_t* data) {
	CD_CREATE_MSG_SIZE_BIN(cd_s_cmd_response, sizeof(cd_s_cmd_response) + len, msg, bin);

	msg->opcode = CD_CMD_RESPONSE;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->response_type = cmd;
	msg->response_id = id;
	msg->error = false;
	msg->response_size = cd_bin_hton16(len);
	memcpy(msg->response_info, data, len);

	return bin;
}

cd_s_cmd_node* cd_cmd_node_alloc(const char* name, cd_s_cmd_node base, uint16_t link_count, cd_uuid_t* links) {
	size_t name_len = strlen(name);
	size_t links_size = sizeof(cd_uuid_t) * link_count;
	size_t remaining_size = sizeof(char) * name_len + links_size;
	cd_s_cmd_node* node = CD_MALLOC(sizeof(cd_s_cmd_node) + remaining_size);
	
	memcpy(node->uuid, base.uuid, sizeof(cd_uuid_t));
	memcpy(node->address, base.address, sizeof(cd_mac_addr_t));
	node->name_len = name_len;
	node->light_on = base.light_on;
	node->provisioned = base.provisioned;
	node->button_pub = cd_bin_hton32(base.button_pub);
	node->link_count = cd_bin_hton16(link_count);
	node->remaining_size = cd_bin_hton16(remaining_size);
	void* cursor = (void*) &node->remaining_data[0];
	memcpy(cursor, name, name_len); // copy name
	cursor += name_len;
	memcpy(cursor, links, links_size); // copy links

	return node;
}

cd_s_cmd_response_get_node* cd_cmd_get_node_res_from_node_arr(uint16_t size, cd_s_cmd_node* arr[]) {
	size_t remaining_size = 0;

	for (unsigned int i = 0; i < size; i++) {
		remaining_size += sizeof(cd_s_cmd_node) + cd_bin_ntoh16(arr[i]->remaining_size);
	}

	cd_s_cmd_response_get_node* response = CD_MALLOC(sizeof(cd_s_cmd_response_get_node) + remaining_size);
	response->node_count = cd_bin_hton16(size);
	response->remaining_size = cd_bin_hton16(remaining_size);

	void* cursor = response->nodes;
	for (unsigned int i = 0; i < size; i++) {
		size_t size = sizeof(cd_s_cmd_node) + cd_bin_ntoh16(arr[i]->remaining_size);
		memcpy(cursor, arr[i], size);
		cursor += size;
	}

	return response;
}

#ifdef __cplusplus
}
#endif

