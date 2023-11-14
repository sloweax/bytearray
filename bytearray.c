#include "bytearray.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

bytearray *bytearray_create(size_t cap)
{
	bytearray *b = malloc(sizeof(bytearray));
	if (b == NULL)
		return NULL;

	uint8_t *data = NULL;

	if (cap > 0) {
		data = malloc(cap);
		if (data == NULL) {
			free(b);
			return NULL;
		}
	}

	b->data = data;
	b->cap = cap;
	b->len = 0;
	return b;
}

void bytearray_free(bytearray *b)
{
	free(b->data);
	free(b);
}

bool bytearray_grow(bytearray *b, size_t cap)
{
	if (cap == 0)
		return true;

	uint8_t *ndata = realloc(b->data, b->cap + cap);

	if (ndata == NULL)
		return false;

	b->data = ndata;
	b->cap += cap;
	return true;
}

bool bytearray_reserve(bytearray *b, size_t cap)
{
	if (cap <= b->cap)
		return true;

	return bytearray_grow(b, cap - b->cap);
}

bool bytearray_cat(bytearray *b, const void *data, size_t len)
{
	if (!bytearray_reserve(b, b->len + len))
		return false;

	memcpy(b->data + b->len, data, len);
	b->len += len;
	return true;
}

bool bytearray_set(bytearray *b, const void *data, size_t len)
{
	if (!bytearray_reserve(b, len))
		return false;

	memcpy(b->data, data, len);
	b->len = len;
	return true;
}
