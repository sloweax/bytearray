#include "unit.h"
#include "../bytearray.h"
#include <string.h>

void test_hexencode(void)
{
	struct bytearray b = BYTEARRAY_STATIC_CREATE(20);
	uint8_t data[5] = { 0x12, 0x34, 0xca, 0xfe, 0xf9 };

	ASSERT(bytearray_hexencode(&b, data, 5));
	ASSERT(memcmp(b.data, "1234cafef9", 10) == 0 && b.len == 10);
	ASSERT(bytearray_hexencode(&b, data, 5));
	ASSERT(memcmp(b.data, "1234cafef91234cafef9", 20) == 0 && b.len == 20);
	ASSERT(!bytearray_hexencode(&b, data, 5));
}

void test_hexdecode(void)
{
	struct bytearray b = BYTEARRAY_STATIC_CREATE(10);
	char *hex = "1234cafef9";
	ASSERT(bytearray_hexdecode(&b, hex, 10) && b.len == 5);
	ASSERT(memcmp(b.data, "\x12\x34\xca\xfe\xf9", 5) == 0);
	ASSERT(bytearray_hexdecode(&b, hex, 8) && b.len == 9);
	ASSERT(memcmp(b.data, "\x12\x34\xca\xfe\xf9\x12\x34\xca\xfe", 6) == 0);
	ASSERT(bytearray_hexdecode(&b, hex, 1) && b.len == 10);
	ASSERT(memcmp(b.data, "\x12\x34\xca\xfe\xf9\x12\x34\xca\xfe\xf0", 6) ==
	       0);
	ASSERT(!bytearray_hexdecode(&b, hex, 1));
}
