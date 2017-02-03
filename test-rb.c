#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "rb.h"

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

int int_cmp(const void *_a, const void *_b, void *p)
{
	intmap_t *a = (intmap_t*)_a;
	intmap_t *b = (intmap_t*)_b;
	return (a->key > b->key) - (a->key < b->key);
}

int test_int(int n)
{
	int i, cnt = 0;
	uint64_t x = 11;
	intmap_t *d, *r;
	struct rb_table *h;

	h = rb_create(int_cmp, 0, 0);
	for (i = 0; i < n; ++i) {
		unsigned y = x % (n>>1);
		x = kad_splitmix64(x);
		d = (intmap_t*)malloc(sizeof(intmap_t));
		d->key = y; d->value = i;
		if (rb_find(h, d) == 0) {
			rb_insert(h, d);
			++cnt;
		} else {
			r = rb_delete(h, d);
			free(d); free(r);
			--cnt;
		}
	}
	rb_destroy(h, 0);
	return cnt;
}

int main(int argc, char *argv[])
{
	int n = 2000000;
	if (argc > 1) n = atoi(argv[1]);
	fprintf(stderr, "%d\n", test_int(n));
	return 0;
}
