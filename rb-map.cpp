#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <map>

static inline uint64_t kad_splitmix64(uint64_t x)
{
	uint64_t z = (x += 0x9E3779B97F4A7C15ULL);
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
	return z ^ (z >> 31);
}

typedef std::map<unsigned, int> intmap_t;

int test_int(int n)
{
	int i, cnt = 0;
	uint64_t x = 11;
	intmap_t *h = new intmap_t;

	for (i = 0; i < n; ++i) {
		unsigned y = x % (n>>1);
		x = kad_splitmix64(x);
		std::pair<intmap_t::iterator, bool> p = h->insert(std::pair<unsigned, int>(y, i));
		if (p.second == false) h->erase(p.first);
	}
	cnt = h->size();
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
