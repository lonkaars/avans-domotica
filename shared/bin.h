#pragma once

/** @file bin.h */

/**
 * helper file for binary data
 *
 * - fix endianness with functions inspired by UNIX arpa/inet.h
 * - convert uint16_t and uint32_t to cd_s_bin
 */

#include <stdint.h>
#include <stdlib.h>

#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t g_cd_endianness;

/** @brief cast `in.data` to `type out` */
#define CD_CAST_BIN(type, in, out) type *out = (type *)&in->data;
#define CD_CREATE_MSG_BIN(type, normal, bin) CD_CREATE_MSG_SIZE_BIN(type, sizeof(type), normal, bin)
/** @brief create cd_s_bin struct with space for struct and cast data field of cd_s_bin to struct pointer */
#define CD_CREATE_MSG_SIZE_BIN(type, size, normal, bin)                                                                                                                            \
	cd_s_bin *bin = CD_MALLOC(sizeof(cd_s_bin) + size);                                                                                                                            \
	bin->bytes	  = size;                                                                                                                                                          \
	type *normal  = (type *)&bin->data;
// TODO: document above macro but better

/** @brief hold binary data with fixed size */
typedef struct {
	uint16_t bytes; /** @brief data size */
	uint8_t data[]; /** @brief data */
} cd_s_bin;

/** @brief allocate new cd_s_bin struct and fill with `*data` for `bytes` bytes */
cd_s_bin *cd_bin_s_alloc(uint16_t bytes, uint8_t *data);
/** @brief concatenate 2 cd_s_bin structs, deallocates `a` and `b` */
cd_s_bin *cd_bin_s_cat(cd_s_bin *a, cd_s_bin *b);

cd_s_bin *cd_bin_from_uint8_t(uint8_t data);
cd_s_bin *cd_bin_from_uint16_t(uint16_t data);
cd_s_bin *cd_bin_from_uint32_t(uint32_t data);

/** @brief convert 32-bit value from host endian to network (big-endian) */
uint32_t cd_bin_hton32(uint32_t h32);
/** @brief convert 16-bit value from host endian to network (big-endian) */
uint16_t cd_bin_hton16(uint16_t h16);
/** @brief convert 32-bit value from network (big-endian) to host endian */
uint32_t cd_bin_ntoh32(uint32_t n32);
/** @brief convert 16-bit value from network (big-endian) to host endian */
uint16_t cd_bin_ntoh16(uint16_t n16);

/**
 * @brief convert (8*s)-bit value from network (big-endian) to host endian
 * (dynamic size)
 *
 * @param n  pointer to number
 * @param s  size of number in bytes
 *
 * @return 32-bit integer regardless of `s`
 *
 * this function is exclusively used by the CD_DYN_MEMBER_SIZEOF macro in
 * shared/protocol.c
 */
uint32_t cd_bin_ntohd(uint8_t *n, size_t s);
uint32_t cd_bin_htond(uint8_t *h, size_t s);

/** @brief replace 32-bit value from host endian to network (big-endian) */
void cd_bin_repl_hton32(uint32_t *h32);
/** @brief replace 16-bit value from host endian to network (big-endian) */
void cd_bin_repl_hton16(uint16_t *h16);
/** @brief replace 32-bit value from network (big-endian) to host endian */
void cd_bin_repl_ntoh32(uint32_t *n32);
/** @brief replace 16-bit value from network (big-endian) to host endian */
void cd_bin_repl_ntoh16(uint16_t *n16);

#ifdef __cplusplus
}
#endif
