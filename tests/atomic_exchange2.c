#define _GNU_SOURCE

char *testcase_description = "Uncontended atomic exchange";

void testcase(unsigned long long *iterations, unsigned long nr)
{
	int val = 0;

	while (1) {
		__sync_bool_compare_and_swap(&val, 0, 1);
		__sync_bool_compare_and_swap(&val, 1, 0);

		(*iterations)++;
	}
}
