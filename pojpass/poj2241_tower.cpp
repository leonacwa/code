#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int NN = 50000;
struct Block {
	int l, w, h;
};
int n;
Block b[NN];
int f[NN];

bool cmp(const Block &a, const Block &b) {
	return a.l > b.l;
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			int l, w, h;
			scanf("%d %d %d", &l, &w, &h);
			b[3*i].l = max(l, w);
			b[3*i].w = min(l, w);
			b[3*i].h = h;
			b[3*i + 1].l = max(h, w);
			b[3*i + 1].w = min(h, w);
			b[3*i + 1].h = l;
			b[3*i + 2].l = max(l, h);
			b[3*i + 2].w = min(l, h);
			b[3*i + 2].h = w;
		}
		n *= 3;
		sort(b, b + n, cmp); 
		f[0] = b[0].h;
		int ans = f[0];
		for (int i = 1; i < n; ++i) {
			f[i] = b[i].h;
			for (int j = 0; j < i; ++j) {
				if (b[j].l > b[i].l && b[j].w > b[i].w) {
					if (f[i] < f[j] + b[i].h) {
						f[i] = f[j] + b[i].h;
					}
				}
			}
			if (ans < f[i]) ans = f[i];
		}
		printf("Case %d: maximum height = %d\n", ++nCase, ans);
	}
	return 0;
}

