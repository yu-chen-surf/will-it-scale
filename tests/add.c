#define _GNU_SOURCE
#include <pthread.h>

char *testcase_description = "Add loop";

unsigned long counter = 0;
unsigned long i = 1;

void testcase(unsigned long long *iterations, unsigned long nr)
{
	while (1) {

		asm volatile("addq %1,%0"
                     : "=m" (counter)
                     : "er" (i), "m" (counter) : "memory");

		(*iterations)++;
	}
}
