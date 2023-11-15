#include "test_bytearray.h"
#include "unit.h"
#include "../bytearray.h"
#include <assert.h>

void test_create(void)
{
	struct bytearray *a = bytearray_create(0);
	assert(a);
	struct bytearray *b = bytearray_create(32);
	assert(a);

	ASSERT(a->len == 0 && a->cap == 0);
	ASSERT(a->flags == BYTEARRAY_DATA_ALLOC + BYTEARRAY_STRUCT_ALLOC);

	ASSERT(b->len == 0 && b->cap == 32 && b->data);
	ASSERT(b->flags == BYTEARRAY_DATA_ALLOC + BYTEARRAY_STRUCT_ALLOC);

	bytearray_free(a);
	bytearray_free(b);
}

void test_static_create(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(32);

	ASSERT(a.len == 0 && a.cap == 32 && a.data);
	ASSERT(!(a.flags & BYTEARRAY_DATA_ALLOC));
	ASSERT(!(a.flags & BYTEARRAY_STRUCT_ALLOC));
}

void test_grow(void)
{
	struct bytearray *a = bytearray_create(0);
	assert(a);

	assert(bytearray_grow(a, 32));
	assert(bytearray_grow(a, 0));

	ASSERT(a->cap == 32 && a->len == 0 && a->data);

	assert(bytearray_grow(a, 32));
	assert(bytearray_grow(a, 0));

	ASSERT(a->cap == 64 && a->len == 0 && a->data);

	bytearray_free(a);
}

void test_static_grow(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(32);
	bool success;

	success = bytearray_grow(&a, 10);

	ASSERT(!success && a.cap == 32 && a.len == 0);

	success = bytearray_grow(&a, 0);

	ASSERT(success && a.cap == 32 && a.len == 0);
}

void test_reserve(void)
{
	struct bytearray *a = bytearray_create(0);
	assert(a);

	ASSERT(bytearray_reserve(a, 0));

	assert(bytearray_reserve(a, 32));

	ASSERT(a->cap == 32 && a->len == 0 && a->data);

	ASSERT(bytearray_reserve(a, 16));
	ASSERT(bytearray_reserve(a, 0));

	ASSERT(a->cap == 32 && a->len == 0 && a->data);

	assert(bytearray_reserve(a, 64));

	ASSERT(a->cap == 64 && a->len == 0 && a->data);

	bytearray_free(a);
}

void test_static_reserve(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(32);
	bool success;

	success = bytearray_reserve(&a, 0);

	ASSERT(success && a.cap == 32 && a.len == 0);

	success = bytearray_reserve(&a, 32);

	ASSERT(success && a.cap == 32 && a.len == 0);

	success = bytearray_reserve(&a, 33);

	ASSERT(!success && a.cap == 32 && a.len == 0);
}

void test_fit(void)
{
	struct bytearray *a = bytearray_create(0);
	assert(a);

	bytearray_free(a);
}
