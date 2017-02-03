#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "rb.hpp"

static inline uint64_t kad_splitmix64(uint64_t x)
{
	uint64_t z = (x += 0x9E3779B97F4A7C15ULL);
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
	return z ^ (z >> 31);
}

struct int_cmp {
	inline int operator () (unsigned a, unsigned b) {
		return (a > b) - (a < b);
	}
};

typedef rbmap_t<unsigned, int, int_cmp> intmap_t;

int test_int(int n)
{
	int i, present, cnt = 0;
	uint64_t x = 11;
	intmap_t *h;
	intmap_t::node_t *p;

	h = new intmap_t;
	for (i = 0; i < n; ++i) {
		unsigned y = x % (n>>1);
		x = kad_splitmix64(x);
		p = h->find(y);
		if (p == 0) {
			p = h->insert(y, &present);
			p->value = i;
			++cnt;
		} else {
			p = h->erase(y);
			free(p);
			--cnt;
		}
	}
	delete h;
	return cnt;
}

int main(int argc, char *argv[])
{
	int n = 2000000;
	if (argc > 1) n = atoi(argv[1]);
	fprintf(stderr, "%d\n", test_int(n));
	return 0;
}
