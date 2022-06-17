#define _GNU_SOURCE
#include <stdlib.h>

char *testcase_description = "Contended atomic exchange with local update";

int val = 0;

void testcase(unsigned long long *iterations, unsigned long nr)
{
	// alloca() because plain "unsigned long val" gets optimized away.
	unsigned long *l_val = alloca(sizeof(unsigned long));
	*(l_val) = 0;

	while (1) {
		__sync_bool_compare_and_swap(&val, 0, 1);
		(*l_val)++;
		__sync_bool_compare_and_swap(&val, 1, 0);

		(*iterations)++;
	}
}
