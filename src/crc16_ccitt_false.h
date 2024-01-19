#ifndef _CRC16_CCITT_FALSE_H_
#define _CRC16_CCITT_FALSE_H_

#include <stddef.h>
#include "common.h"

u64 crc16_ccitt_false_compute(const u8 *data, size_t length);

#endif  // _CRC16_CCITT_FALSE_H_

