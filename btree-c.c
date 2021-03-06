#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "kbtree.h"

static inline uint64_t kad_splitmix64(uint64_t x)
{
	uint64_t z = (x += 0x9E3779B97F4A7C15ULL);
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
	return z ^ (z >> 31);
}

typedef struct {
	unsigned key;
	int value;
} intmap_t;

#define int_cmp(a, b) (((a).key > (b).key) - ((a).key < (b).key))
KBTREE_INIT(bt, intmap_t, int_cmp)

int test_int(int n)
{
	int i, cnt = 0;
	uint64_t x = 11;
	intmap_t d;
	kbtree_t(bt) *h;

	h = kb_init(bt, KB_DEFAULT_SIZE);
	for (i = 0; i < n; ++i) {
		unsigned y = x % (n>>1);
		x = kad_splitmix64(x);
		d.key = y, d.value = i;
		if (kb_getp(bt, h, &d) == 0)
			kb_putp(bt, h, &d);
		else kb_delp(bt, h, &d);
	}
	cnt = kb_size(h);
	kb_destroy(bt, h);
	return cnt;
}

int main(int argc, char *argv[])
{
	int n = 2000000;
	if (argc > 1) n = atoi(argv[1]);
	fprintf(stderr, "%d\n", test_int(n));
	return 0;
}
