#include <memory.h>

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
	memcpy(&msg->uuid, &uuid, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_led(bool on, cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_led, msg, bin);

	msg->opcode = CD_CMD_POST_LED;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->on = on;
	memcpy(&msg->uuid, &uuid, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_link_add(cd_uuid_t button, cd_uuid_t light, cd_e_cmd_link_type type) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_link, msg, bin);

	msg->opcode = CD_CMD_POST_LINK;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->add = true;
	memcpy(&msg->button, &button, sizeof(cd_uuid_t));
	memcpy(&msg->led, &light, sizeof(cd_uuid_t));
	msg->type = type;

	return bin;
}

cd_s_bin* cd_cmd_gen_post_link_rm(cd_uuid_t button, cd_uuid_t light) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_link, msg, bin);

	msg->opcode = CD_CMD_POST_LINK;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->add = false;
	memcpy(&msg->button, &button, sizeof(cd_uuid_t));
	memcpy(&msg->led, &light, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_net_add(cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_net, msg, bin);

	msg->opcode = CD_CMD_POST_NET;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->join = true;
	memcpy(&msg->uuid, &uuid, sizeof(cd_uuid_t));

	return bin;
}

cd_s_bin* cd_cmd_gen_post_net_rm(cd_uuid_t uuid) {
	CD_CREATE_MSG_BIN(cd_s_cmd_post_net, msg, bin);

	msg->opcode = CD_CMD_POST_NET;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->join = false;
	memcpy(&msg->uuid, &uuid, sizeof(cd_uuid_t));

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

cd_s_bin* cd_cmd_res_get_node(cd_e_scmds cmd, cd_cmd_id_t id, uint16_t node_count, cd_s_cmd_node* nodes) {
	CD_CREATE_MSG_BIN(cd_s_cmd_response, msg, bin);

	msg->opcode = CD_CMD_RESPONSE;
	msg->id = cd_bin_hton16(cd_protocol_fresh_message_id());
	msg->response_type = cmd;
	msg->response_id = id;
	msg->error = false;

	// TODO: test this??
	msg->response_size = sizeof(cd_s_cmd_response_get_node) + sizeof(cd_s_cmd_node) * node_count;
	cd_s_cmd_response_get_node* get_node_response_ptr = (cd_s_cmd_response_get_node*) msg->response_info;
	memcpy(get_node_response_ptr->nodes, nodes, sizeof(cd_s_cmd_node) * node_count);

	return bin;
}

#ifdef __cplusplus
}
#endif

