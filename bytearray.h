#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  size_t cap;
  size_t len;
  uint8_t *data;
} bytearray;

bytearray *bytearray_create(size_t cap);
void bytearray_free(bytearray *b);
bool bytearray_grow(bytearray *b, size_t cap);
bool bytearray_reserve(bytearray *b, size_t cap);
bool bytearray_set(bytearray *b, const void *data, size_t len);
bool bytearray_cat(bytearray *b, const void *data, size_t len);
bool bytearray_read(bytearray *b, int fd);
bool bytearray_nread(bytearray *b, int fd, size_t max);
void bytearray_clear(bytearray *b);
bool bytearray_fit(bytearray *b);
