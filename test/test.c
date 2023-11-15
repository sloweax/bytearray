#include <stdio.h>
#include "test_bytearray.h"
#include "unit.h"

int main()
{
	test_create();
	test_static_create();
	test_grow();
	test_static_grow();
	test_reserve();
	test_static_reserve();
	test_fit();
	test_static_fit();
	test_init();
	test_set();
	test_cat();
	result();
}
