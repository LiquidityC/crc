#include "crc32.h"
#include <zlib.h>

u64 crc32_compute(const u8 *data, size_t len)
{
	return crc32(0, data, len);
}
