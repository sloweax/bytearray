#include "bytearray.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct bytearray *bytearray_create(size_t cap)
{
	struct bytearray *b = malloc(sizeof(struct bytearray));
	if (b == NULL)
		return NULL;

	b->data = malloc(cap);

	if (b->data == NULL && cap != 0) {
		free(b);
		return NULL;
	}

	b->flags = BYTEARRAY_STRUCT_ALLOC + BYTEARRAY_DATA_ALLOC;
	b->cap = cap;
	b->len = 0;
	return b;
}

void bytearray_free(struct bytearray *b)
{
	if (b->data && b->flags & BYTEARRAY_DATA_ALLOC)
		free(b->data);
	if (b->flags & BYTEARRAY_STRUCT_ALLOC)
		free(b);
}

bool bytearray_grow(struct bytearray *b, size_t cap)
{
	if (cap == 0)
		return true;

	if (!(b->flags & BYTEARRAY_DATA_ALLOC))
		return false;

	uint8_t *ndata = realloc(b->data, b->cap + cap);

	if (ndata == NULL)
		return false;

	b->data = ndata;
	b->cap += cap;
	return true;
}

bool bytearray_reserve(struct bytearray *b, size_t cap)
{
	if (cap <= b->cap)
		return true;

	return bytearray_grow(b, cap - b->cap);
}

bool bytearray_cat(struct bytearray *b, const void *data, size_t len)
{
	if (!bytearray_reserve(b, b->len + len))
		return false;

	memcpy(b->data + b->len, data, len);
	b->len += len;
	return true;
}

bool bytearray_set(struct bytearray *b, const void *data, size_t len)
{
	if (!bytearray_reserve(b, len))
		return false;

	memcpy(b->data, data, len);
	b->len = len;
	return true;
}

void bytearray_clear(struct bytearray *b)
{
	b->len = 0;
}

bool bytearray_fit(struct bytearray *b)
{
	if (b->len == b->cap || !(b->flags & BYTEARRAY_DATA_ALLOC))
		return true;

	if (b->len == 0) {
		free(b->data);
		b->data = NULL;
		b->cap = 0;
	} else {
		uint8_t *ndata = realloc(b->data, b->len);
		if (ndata == NULL)
			return false;

		b->cap = b->len;
		b->data = ndata;
	}

	return true;
}

void bytearray_init(struct bytearray *b)
{
	b->cap = b->len = 0;
	b->data = NULL;
	b->flags = BYTEARRAY_DATA_ALLOC;
}
