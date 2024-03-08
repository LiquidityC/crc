#ifndef _CRC32_H_
#define _CRC32_H_

#include <stddef.h>
#include "common.h"

u64 crc32_compute(const u8 *data, size_t len);

#endif // _CRC32_H_
