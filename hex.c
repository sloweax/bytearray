#include "bytearray.h"

bool bytearray_hexencode(struct bytearray *b, const void *data, size_t len)
{
	if (!bytearray_reserve(b, b->len + len * 2))
		return false;

	char hex[16] = "0123456789abcdef";

	for (size_t i = 0; i < len; i++) {
		b->data[b->len++] = hex[((uint8_t *)data)[i] >> 4];
		b->data[b->len++] = hex[((uint8_t *)data)[i] & 0x0f];
	}

	return true;
}

bool bytearray_hexdecode(struct bytearray *b, const void *data, size_t len)
{
	if (!bytearray_reserve(b, b->len + (len / 2) + (len % 2)))
		return false;

	uint8_t tmp;
	for (size_t i = 0; i < len; i++) {
		tmp = ((uint8_t *)data)[i];

		if (tmp <= '9')
			tmp -= '0';
		else if (tmp <= 'f')
			tmp = tmp + 10 - 'a';
		else
			tmp = tmp + 10 - 'A';

		if (i % 2)
			b->data[b->len++] += tmp;
		else
			b->data[b->len] = tmp << 4;
	}

	if (len == 1)
		b->len++;

	return true;
}
