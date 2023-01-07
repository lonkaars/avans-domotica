#include <stddef.h>

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

cd_cmd_id_t g_cd_protocol_fresh_message_id = 0;

size_t cd_cmd_sizeof(uint8_t data[CD_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	cd_cmd_opcode_t opcode = data[0];
	if (CD_CMD_HANDLERS_SIZE[opcode] > 0) return CD_CMD_HANDLERS_SIZE[opcode];

	cd_s_bin *copy = cd_bin_s_alloc(data_length, data);
	size_t length  = (*CD_CMD_HANDLERS_SIZEOF[opcode])(copy);

	CD_FREE(copy);

	return length;
}

/**
 * @brief macro to calculate size of message based on struct with member to
 * indicate length of dynamic (last) field
 *
 * @param data  cd_s_bin pointer to currently received data
 * @param struct_t  message struct
 * @param length_field  struct field with dynamic length
 *
 * @return size_t with calculated size
 *
 * equivalent c code:
 *
 * size_t size = sizeof(struct_t);
 * size_t dyn_member_offset = offsetof(struct_t, length_field);
 * size_t dyn_member_size = sizeof(((struct_t*)0)->length_field);
 * if (data->bytes >= (dyn_member_offset + dyn_member_size))
 *     size += cd_bin_ntohd(&data->data[dyn_member_offset], dyn_member_size);
 * return size;
 */
#define CD_DYN_MEMBER_SIZEOF(data, struct_t, length_field)                                                                                                                         \
	sizeof(struct_t) + ((data->bytes >= (offsetof(struct_t, length_field) + sizeof(((struct_t *)0)->length_field)))                                                                \
							? (cd_bin_ntohd(&data->data[offsetof(struct_t, length_field)], sizeof(((struct_t *)0)->length_field)))                                                 \
							: 0);

size_t cd_cmd_response_sizeof(cd_s_bin *data) { return CD_DYN_MEMBER_SIZEOF(data, cd_s_cmd_response, response_size); }

cd_cmd_id_t cd_protocol_fresh_message_id() { return g_cd_protocol_fresh_message_id++; }

#ifdef __cplusplus
}
#endif
