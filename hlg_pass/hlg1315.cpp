#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 1000;
struct Node {
	int a, b;
	bool operator < (const Node &B) const {
		if (a != B.a) return a < B.a;
		return b < B.b;
	}
};
Node ap[NN];
int f[NN];
int n;

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &ap[i].a, &ap[i].b);
		}
		sort(ap, ap+n);
		f[0] = 1;
		int ans = 1;
		for (int i = 1; i < n; ++i) {
			f[i] = 1;
			for (int j = 0; j < i; ++j) {
				if (ap[j].b <= ap[i].a && f[i] < f[j] + 1) {
					f[i] = f[j] + 1;
				}
			}
			if (ans < f[i]) ans = f[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

