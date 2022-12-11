#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t cd_cmd_sizeof(uint8_t data[CD_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	cd_cmd_opcode_t opcode = data[0];
	if (CD_CMD_HANDLERS_SIZE[opcode] > 0) return CD_CMD_HANDLERS_SIZE[opcode];

	cd_s_bin *copy = cd_bin_s_alloc(data_length, data);
	size_t length = (*CD_CMD_HANDLERS_SIZEOF[opcode])(copy);

	free(copy);

	return length;
}

#define CD_DYN_MEMBER_SIZEOF(struct_t, length_byte, trailing_type)                                 \
	sizeof(struct_t) +                                                                             \
		(data->bytes > length_byte ? (sizeof(trailing_type) * data->data[length_byte]) : 0)

size_t cd_cmd_response_sizeof(cd_s_bin* data) {
	(void) data; // unused variable TODO: implement this
	return 0;
}

#ifdef __cplusplus
}
#endif
