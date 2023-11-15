#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct bytearray {
  size_t cap;
  size_t len;
  uint32_t flags;
  uint8_t *data;
};

enum bytearray_flags {
  BYTEARRAY_DATA_ALLOC = 1 << 0,
  BYTEARRAY_STRUCT_ALLOC = 1 << 1,
};

#define BYTEARRAY_STATIC_CREATE(CAP) { \
    .flags = 0, \
    .len = 0, \
    .cap = (CAP), \
    .data = (uint8_t[CAP]){0} \
  }

struct bytearray *bytearray_create(size_t cap);
void bytearray_free(struct bytearray * b);
bool bytearray_grow(struct bytearray * b, size_t cap);
bool bytearray_reserve(struct bytearray * b, size_t cap);
bool bytearray_set(struct bytearray * b, const void *data, size_t len);
bool bytearray_cat(struct bytearray * b, const void *data, size_t len);
bool bytearray_read(struct bytearray * b, int fd);
bool bytearray_nread(struct bytearray * b, int fd, size_t max);
void bytearray_clear(struct bytearray * b);
bool bytearray_fit(struct bytearray * b);
