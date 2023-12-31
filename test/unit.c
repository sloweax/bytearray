#include "unit.h"
#include <stdio.h>
#include <string.h>

#define END "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

char *last_fname = "";
int fail_count;
int ok_count;

void test(int status, const char *funcname, const char *fname,
	  const char *assertion, int line)
{
	if (strcmp(funcname, last_fname) != 0) {
		last_fname = (char *)funcname;
		printf("\n%s()\n\n", funcname);
	}

	printf("    %-80s", assertion);

	if (!status) {
		ok_count++;
		puts(GREEN "OK" END);
	} else {
		fail_count++;
		printf(RED "FAILED" END " %s:%d\n", fname, line);
	}
}

void result(void)
{
	printf("\nresult: %s\n"
	       "total: %d passed: %d failed: %d\n\n",
	       fail_count > 0 ? RED "FAILED" END : GREEN "PASS" END,
	       ok_count + fail_count, ok_count, fail_count);
}
