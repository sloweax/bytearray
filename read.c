#include "bytearray.h"

#include <string.h>
#include <unistd.h>

#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) < (y) ? (x) : (y)

bool bytearray_read(struct bytearray *b, int fd)
{
	uint8_t buf[2048];
	ssize_t n;

	while ((n = read(fd, buf, sizeof(buf)))) {
		if (n == -1)
			return false;

		if (b->len + n > b->cap) {
			if (!bytearray_reserve(b, MAX(b->cap * 2, n + b->cap)))
				return false;
		}

		memcpy(b->data + b->len, buf, n);
		b->len += n;
	}

	return true;
}

bool bytearray_nread(struct bytearray *b, int fd, size_t max)
{
	uint8_t buf[2048];
	ssize_t n;
	size_t total = 0;

	if (!bytearray_reserve(b, b->len + max))
		return false;

	while (total < max &&
	       (n = read(fd, buf, MIN(sizeof(buf), max - total)))) {
		if (n == -1)
			return false;

		memcpy(b->data + b->len, buf, n);
		b->len += n;
		total += n;
	}

	return true;
}
