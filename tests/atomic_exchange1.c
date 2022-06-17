#define _GNU_SOURCE

char *testcase_description = "Contended atomic exchange";

int val = 0;

void testcase(unsigned long long *iterations, unsigned long nr)
{
	while (1) {
		__sync_bool_compare_and_swap(&val, 0, 1);
		__sync_bool_compare_and_swap(&val, 1, 0);

		(*iterations)++;
	}
}
