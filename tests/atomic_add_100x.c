#define _GNU_SOURCE
#include <pthread.h>

char *testcase_description = "Atomic Add loop 100x";

unsigned long counter = 0;
unsigned long i = 1;

#define ONE asm volatile("lock addq %1,%0"     : "=m" (counter)        : "er" (i), "m" (counter) : "memory");
#define TEN     ONE ONE ONE ONE ONE ONE ONE ONE ONE ONE
#define HUNDRED TEN TEN TEN TEN TEN TEN TEN TEN TEN TEN

void testcase(unsigned long long *iterations, unsigned long nr)
{
	while (1) {
		HUNDRED
		(*iterations) = (*iterations) + 100;
	}
}
