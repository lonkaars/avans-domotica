#include <stdlib.h>
#include <string.h>

#include "bin.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CD_ENDIAN_LITTLE (1)
#define CD_ENDIAN_BIG (0)

#define _SHIFT_0B (8 * 0)
#define _SHIFT_1B (8 * 1)
#define _SHIFT_2B (8 * 2)
#define _SHIFT_3B (8 * 3)
#define _BYTE_0 ((uint32_t)0xff << (_SHIFT_0B))
#define _BYTE_1 ((uint32_t)0xff << (_SHIFT_1B))
#define _BYTE_2 ((uint32_t)0xff << (_SHIFT_2B))
#define _BYTE_3 ((uint32_t)0xff << (_SHIFT_3B))

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
cd_s_bin *cd_bin_from_uint8_t(uint8_t data) {
	size_t size	  = 1;
	cd_s_bin *ret = malloc(sizeof(cd_s_bin) + sizeof(uint8_t) * size);
	ret->bytes	  = size;
	ret->data[0]  = data;
	return ret;
}

cd_s_bin *cd_bin_from_uint16_t(uint16_t data) {
	size_t size	  = 2;
	cd_s_bin *ret = malloc(sizeof(cd_s_bin) + sizeof(uint8_t) * size);
	data		  = cd_bin_hton16(data);
	ret->bytes	  = size;
	ret->data[0]  = (data & _BYTE_1) >> _SHIFT_1B;
	ret->data[1]  = (data & _BYTE_0) >> _SHIFT_0B;
	return ret;
}

cd_s_bin *cd_bin_from_uint32_t(uint32_t data) {
	size_t size	  = 4;
	cd_s_bin *ret = malloc(sizeof(cd_s_bin) + sizeof(uint8_t) * size);
	data		  = cd_bin_hton32(data);
	ret->bytes	  = size;
	ret->data[0]  = (data & _BYTE_3) >> _SHIFT_3B;
	ret->data[1]  = (data & _BYTE_2) >> _SHIFT_2B;
	ret->data[2]  = (data & _BYTE_1) >> _SHIFT_1B;
	ret->data[3]  = (data & _BYTE_0) >> _SHIFT_0B;
	return ret;
}

uint32_t cd_bin_hton32(uint32_t h32) {
	if (g_cd_endianness == CD_ENDIAN_BIG) return h32;
	return ((h32 & _BYTE_0) << _SHIFT_3B) | ((h32 & _BYTE_1) << _SHIFT_1B) |
		   ((h32 & _BYTE_2) >> _SHIFT_1B) | ((h32 & _BYTE_3) >> _SHIFT_3B);
}
#pragma GCC diagnostic pop

uint16_t cd_bin_hton16(uint16_t h16) {
	if (g_cd_endianness == CD_ENDIAN_BIG) return h16;
	return ((h16 & _BYTE_0) << _SHIFT_1B) | ((h16 & _BYTE_1) >> _SHIFT_1B);
}

uint32_t cd_bin_ntoh32(uint32_t n32) { return cd_bin_hton32(n32); }
uint16_t cd_bin_ntoh16(uint16_t n16) { return cd_bin_hton16(n16); }

cd_s_bin *cd_bin_s_alloc(uint16_t bytes, uint8_t *data) {
	cd_s_bin *temp = malloc(sizeof(cd_s_bin) + sizeof(uint8_t) * bytes);
	temp->bytes	   = bytes;
	memcpy(&temp->data, data, bytes);
	return temp;
}

cd_s_bin *cd_bin_s_cat(cd_s_bin *a, cd_s_bin *b) {
	uint8_t data[a->bytes + b->bytes];
	memcpy(data, a->data, a->bytes);
	memcpy(data + a->bytes, b->data, b->bytes);
	cd_s_bin *c = cd_bin_s_alloc(a->bytes + b->bytes, data);
	free(a);
	free(b);
	return c;
}

void cd_bin_repl_hton32(uint32_t *h32) { *h32 = cd_bin_hton32(*h32); }
void cd_bin_repl_hton16(uint16_t *h16) { *h16 = cd_bin_hton16(*h16); }
void cd_bin_repl_ntoh32(uint32_t *h32) { *h32 = cd_bin_ntoh32(*h32); }
void cd_bin_repl_ntoh16(uint16_t *h16) { *h16 = cd_bin_ntoh16(*h16); }

#ifdef __cplusplus
}
#endif
