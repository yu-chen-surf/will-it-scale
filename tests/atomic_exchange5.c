#define _GNU_SOURCE
#include <pthread.h>

char *testcase_description = "Contended atomic exchange with TLS update";

int val = 0;
__thread unsigned long tls_val;

void testcase(unsigned long long *iterations, unsigned long nr)
{
	while (1) {
		__sync_bool_compare_and_swap(&val, 0, 1);
		tls_val++;
		__sync_bool_compare_and_swap(&val, 1, 0);

		(*iterations)++;
	}
}
