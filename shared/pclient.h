#pragma once

/** @file pclient.h */

#include <stdbool.h>

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief send data over platform standard serial out (doesn't free `data`) */
void cd_pclient_send(cd_s_bin* data);

/** @brief generate PING command */
cd_s_bin* cd_cmd_gen_ping();
/**
 * @brief generate GET_NODE command
 * @param all  get all nodes
 * @param uuid  get specific node by uuid
 */
cd_s_bin* cd_cmd_gen_get_node(bool all, cd_uuid_t uuid);
/**
 * @brief generate POST_LED command
 * @param on  light status
 * @param uuid  node to set light of
 */
cd_s_bin* cd_cmd_gen_post_led(bool on, cd_uuid_t uuid);
/**
 * @brief generate POST_LINK command to add or update link
 * @param button  button node uuid
 * @param light  light node uuid
 * @param type  type of link to set
 */
cd_s_bin* cd_cmd_gen_post_link_add(cd_uuid_t button, cd_uuid_t light, cd_e_cmd_link_type type);
/**
 * @brief generate POST_LINK command to remove link
 * @param button  button node uuid
 * @param light  light node uuid
 */
cd_s_bin* cd_cmd_gen_post_link_rm(cd_uuid_t button, cd_uuid_t light);
/**
 * @brief generate POST_NET command to provision node into network
 * @param uuid  node uuid
 */
cd_s_bin* cd_cmd_gen_post_net_add(cd_uuid_t uuid);
/**
 * @brief generate POST_NET command to provision node out of network
 * @param uuid  node uuid
 */
cd_s_bin* cd_cmd_gen_post_net_rm(cd_uuid_t uuid);

/**
 * @brief generate generic RESPONSE command with error field and no response_info
 * @param cmd  original command opcode
 * @param id  original command id
 * @param error  `true` if some error occurred
 */
cd_s_bin* cd_cmd_res_status(cd_e_scmds cmd, cd_cmd_id_t id, bool error);
/**
 * @brief generate RESPONSE command with GET_NODE response_info
 * @param cmd  original command opcode
 * @param id  original command id
 * @param node_count  amount of nodes in `nodes`
 * @param nodes  pointer to array of `cd_s_cmd_node`
 */
cd_s_bin* cd_cmd_res_get_node(cd_e_scmds cmd, cd_cmd_id_t id, uint16_t node_count, cd_s_cmd_node* nodes);

#ifdef __cplusplus
}
#endif
