#pragma once

/** @file pclient.h */

#include <stdbool.h>

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief send data over platform standard serial out (doesn't free `data`) */
void cd_pclient_send(cd_s_bin *data);

/** @brief generate PING command */
cd_s_bin *cd_cmd_gen_ping();
/**
 * @brief generate GET_NODE command
 * @param all  get all nodes
 * @param uuid  get specific node by uuid
 */
cd_s_bin *cd_cmd_gen_get_node(bool all, cd_uuid_t uuid);
/**
 * @brief generate POST_LED command
 * @param on  light status
 * @param uuid  node to set light of
 */
cd_s_bin *cd_cmd_gen_post_led(bool on, cd_uuid_t uuid);
/**
 * @brief generate POST_LINK command to add or update link
 * @param button  button node uuid
 * @param light  light node uuid
 * @param type  type of link to set
 */
cd_s_bin *cd_cmd_gen_post_link_add(cd_uuid_t button, cd_uuid_t light, cd_e_cmd_link_type type);
/**
 * @brief generate POST_LINK command to remove link
 * @param button  button node uuid
 * @param light  light node uuid
 */
cd_s_bin *cd_cmd_gen_post_link_rm(cd_uuid_t button, cd_uuid_t light);
/**
 * @brief generate POST_NET command to provision node into network
 * @param uuid  node uuid
 */
cd_s_bin *cd_cmd_gen_post_net_add(cd_uuid_t uuid);
/**
 * @brief generate POST_NET command to provision node out of network
 * @param uuid  node uuid
 */
cd_s_bin *cd_cmd_gen_post_net_rm(cd_uuid_t uuid);

/**
 * @brief generate generic RESPONSE command with error field and no response_info
 * @param cmd  original command opcode
 * @param id  original command id
 * @param error  `true` if some error occurred
 */
cd_s_bin *cd_cmd_res_status(cd_e_scmds cmd, cd_cmd_id_t id, bool error);
/**
 * @brief generate RESPONSE command with response_info
 * @param cmd  original command opcode
 * @param id  original command id
 * @param len  size of `data` in bytes
 * @param data  pointer to data
 */
cd_s_bin *cd_cmd_res(cd_e_scmds cmd, cd_cmd_id_t id, uint16_t len, uint8_t *data);
/**
 * @brief generate cd_s_cmd_response_get_node struct from array of cd_s_cmd_node pointers
 * @param size  length of array
 * @param arr  array of pointer to cd_s_cmd_node
 */
cd_s_cmd_response_get_node *cd_cmd_get_node_res_from_node_arr(uint16_t size, cd_s_cmd_node *arr[]);
/**
 * @brief allocate and fill cd_s_cmd_node struct
 *
 * @param base  base struct with values that can be initialized using an initialization list
 * @param name  node name (length is calculated at runtime using strlen())
 * @param link_count  amount of lights this node controls
 * @param links  array of light node uuids
 */
cd_s_cmd_node *cd_cmd_node_alloc(const char *name, cd_s_cmd_node base, uint16_t link_count, cd_uuid_t *links);

#define cd_remaining_sizeof(type, input_struct) ((sizeof(type) + cd_bin_ntoh16(input_struct->remaining_size)) /* NOLINT */)
#define cd_cmd_node_sizeof(node) (cd_remaining_sizeof(cd_s_cmd_node, node) /* NOLINT */)
#define cd_cmd_response_get_node_sizeof(res) (cd_remaining_sizeof(cd_s_cmd_response_get_node, res) /* NOLINT */)

#ifdef __cplusplus
}
#endif
