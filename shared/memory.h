#pragma once

/**
 * @file memory.h  macro's for malloc() and free()
 *
 * these are usually defined in clib's stdlib.h, but zephyr requires the use of
 * the k_malloc and k_free functions for memory management, thus this file is
 * used to set aliases for each respecive platform's native memory management
 * functions as they have the same function signature. these macro's should be
 * defined using a compiler flag
 */

#ifndef CD_MALLOC
#warning CD_MALLOC is not defined, please update build flags to add -DCD_MALLOC <implementation>
#define CD_MALLOC(n) 0
#endif

#ifndef CD_FREE
#warning CD_FREE is not defined, please update build flags to add -DCD_FREE <implementation>
#define CD_FREE(n) ((void)(0))
#endif
