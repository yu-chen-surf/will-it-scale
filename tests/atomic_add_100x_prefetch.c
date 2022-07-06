#define _GNU_SOURCE
#include <pthread.h>

char *testcase_description = "Atomic Add prefetch loop 100x";

unsigned long counter = 0;
unsigned long i = 1;

#define ONE asm volatile("lock addq %1,%0"     : "=m" (counter)        : "er" (i), "m" (counter) : "memory");
#define TEN     ONE ONE ONE ONE ONE ONE ONE ONE ONE ONE
#define HUNDRED TEN TEN TEN TEN TEN TEN TEN TEN TEN TEN

#define BASE_PREFETCH	"prefetcht0 %P1"
#define PREFETCHNTA	"prefetchnta %P1"
#define PREFETCHW	"prefetchw %P1"

void testcase(unsigned long long *iterations, unsigned long nr)
{
	while (1) {
		asm volatile(BASE_PREFETCH
		     : : "i" (0),
		     "m" (*(const char *)iterations));
		HUNDRED
		(*iterations) = (*iterations) + 100;
	}
}
