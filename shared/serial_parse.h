#pragma once

/** @file serial_parse.h */

#include <stdint.h>
#include <stdbool.h>

#include "protocol.h"

#define CD_SERIAL_READ_SUCCESS true
#define CD_SERIAL_READ_FAILURE false

#ifdef __cplusplus
extern "C" {
#endif

/**
 * parse serial data byte by byte
 * @return true if read success, false if read fails
 */
bool cd_serial_parse(uint8_t byte);

#ifdef __cplusplus
}
#endif

