#include "test_bytearray.h"
#include "unit.h"
#include "../bytearray.h"
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

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

	assert(bytearray_fit(a));

	ASSERT(a->cap == 0 && a->len == 0);

	bytearray_free(a);

	a = bytearray_create(32);
	assert(a);
	a->len++;

	assert(bytearray_fit(a));

	ASSERT(a->cap == 1 && a->len == 1 && a->data);

	a->len = 0;
	assert(bytearray_fit(a));

	ASSERT(a->cap == 0 && a->len == 0 && a->data == NULL);

	bytearray_free(a);
}

void test_static_fit(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(32);
	ASSERT(bytearray_fit(&a));
	ASSERT(a.cap == 32 && a.len == 0 && a.data);
}

void test_init(void)
{
	struct bytearray a;
	bytearray_init(&a);

	ASSERT(a.cap == 0 && a.len == 0);
	ASSERT(!(a.flags & BYTEARRAY_STRUCT_ALLOC));
	ASSERT(a.flags & BYTEARRAY_DATA_ALLOC);
}

void test_set(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(10);

	ASSERT(bytearray_set(&a, "abc", 4));
	ASSERT(a.len == 4 && a.cap == 10);
	ASSERT(strcmp((char *)a.data, "abc") == 0);

	ASSERT(bytearray_set(&a, "a", 2));
	ASSERT(a.len == 2 && a.cap == 10);
	ASSERT(strcmp((char *)a.data, "a") == 0);

	ASSERT(bytearray_set(&a, "a", 0));
	ASSERT(a.len == 0 && a.cap == 10);

	ASSERT(!bytearray_set(&a, "1234567890", 11));

	ASSERT(a.len == 0 && a.data[0] != '1');
}

void test_cat(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(10);

	ASSERT(bytearray_cat(&a, "abc", 3));
	ASSERT(bytearray_cat(&a, "123", 4));
	ASSERT(bytearray_cat(&a, "xyz", 0));
	ASSERT(a.len == 7 && a.cap == 10);
	ASSERT(strcmp((char *)a.data, "abc123") == 0);

	ASSERT(!bytearray_cat(&a, "1234567890", 11));

	ASSERT(a.len == 7 && a.cap == 10);
	ASSERT(strcmp((char *)a.data, "abc123") == 0);
}
