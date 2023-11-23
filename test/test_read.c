#include "test_bytearray.h"
#include "unit.h"
#include "../bytearray.h"
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void test_read(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(10);

	int fd = open("test.txt", O_RDONLY); // 'Hello\n'
	assert(fd != -1);

	ASSERT(bytearray_read(&a, fd));
	ASSERT(a.len == 6 && a.cap == 10);
	ASSERT(memcmp(a.data, "Hello\n", 6) == 0);

	assert(lseek(fd, 0, SEEK_SET) != -1);

	ASSERT(!bytearray_read(&a, fd));
	ASSERT(memcmp(a.data, "Hello\n", 6) == 0);

	close(fd);
}

void test_nread(void)
{
	struct bytearray a = BYTEARRAY_STATIC_CREATE(10);

	int fd = open("test.txt", O_RDONLY); // 'Hello\n'
	assert(fd != -1);

	ASSERT(bytearray_nread(&a, fd, 3));
	ASSERT(a.len == 3);
	ASSERT(bytearray_nread(&a, fd, 7));
	ASSERT(bytearray_nread(&a, fd, 0));
	ASSERT(a.len == 6 && a.cap == 10);
	ASSERT(memcmp(a.data, "Hello\n", 6) == 0);
	ASSERT(!bytearray_nread(&a, fd, 100));

	close(fd);
}
