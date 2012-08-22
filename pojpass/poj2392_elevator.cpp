#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 401;
const int AA = 40000 + 1;
struct Block{
	int h, a, c;
};
int n;
Block b[NN];
bool f[AA];

bool cmp(const Block &a, const Block &b) {
	return a.a < b.a;
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		int maxa = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d", &b[i].h, &b[i].a, &b[i].c);
			if (maxa < b[i].a) maxa = b[i].a;
		}
		sort(b, b+n, cmp);
		memset(f, 0, sizeof(f));
		f[0] = true;
		for (int i = 0; i < n; ++i) {
			int k = 1, c = b[i].c;
			while (c) {
				if (k > c) {
					k = c;
				}
				c -= k;
				int sa = k * b[i].h;
				for (int a = b[i].a; a >= sa; --a) {
					f[a] = f[a] || f[a - sa];
				}
				k <<= 1;
			}
		}
		while (!f[maxa]) {
			--maxa;
		}
		printf("%d\n", maxa);
	}
	return 0;
}

