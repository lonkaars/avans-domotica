#include <memory.h>
#include <string.h>

#include "consts.h"
#include "serial_parse.h"

#ifdef __cplusplus
extern "C" {
#endif

bool cd_serial_parse(uint8_t byte) {
	static uint8_t current_message[CD_SERIAL_READ_BUFFER_SIZE] = {0};
	static uint8_t current_message_index					   = 0;
	static uint8_t complete_message_length					   = 2;

	static bool attentive = false;
	static bool listening = false;

	if (byte == CD_SERIAL_START_BYTE) {
		attentive = !attentive;
		if (attentive && listening) return CD_SERIAL_READ_SUCCESS;
	} else if (attentive) {
		attentive = false;
		listening = !listening;
		if (!listening) return CD_SERIAL_READ_FAILURE;
	}

	if (!listening) return CD_SERIAL_READ_SUCCESS;
	current_message[current_message_index++] = byte;

	complete_message_length = cd_cmd_sizeof(current_message, current_message_index);

	if (current_message_index == complete_message_length) {
		cd_cmd_handle(current_message, current_message_index);

		memset(&current_message, 0, CD_SERIAL_READ_BUFFER_SIZE);
		current_message_index	= 0;
		complete_message_length = 1;
		attentive				= false;
		listening				= false;
		return CD_SERIAL_READ_SUCCESS;
	}

	return CD_SERIAL_READ_SUCCESS;
}

void cd_cmd_handle(uint8_t data[CD_SERIAL_READ_BUFFER_SIZE], uint8_t data_length) {
	cd_s_bin *copy = cd_bin_s_alloc(data_length, data);

	if (data[0] >= CD_CMD_COUNT) return;
	cd_cmd_handler_t *handler = CD_CMD_HANDLERS[data[0]];

	if (handler == NULL) return;
	(*handler)(copy);

	CD_FREE(copy);
}

#ifdef __cplusplus
}
#endif
