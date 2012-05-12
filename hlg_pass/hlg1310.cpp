#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	int f, l, n;
	char info[505][101];
	bool operator < (const Node &b) const {
		if (f != b.f) return f > b.f;
		if (l != b.l) return l > b.l;
		int i, ret = 0;
		for (i = 0; i < n; ++i) {
			ret = strcmp(info[i], b.info[i]);
			if (ret != 0) return ret < 0;
		}
		return false;
	}
};

Node ap[501];
int m, n, k;

int main()
{
	while (EOF != scanf("%d %d %d", &m, &n, &k)) {
		for (int i = 0; i < m; ++i) {
			ap[i].n = n;
			for (int j = 0; j < n; ++j) {
				scanf("%s", ap[i].info[j]);
			}
			scanf("%d %d", &ap[i].f, &ap[i].l);
		}
		sort(ap, ap+m);
		for (int i = 0; i < k && i < m; ++i) {
			puts(ap[i].info[0]);
		}
	}
	return 0;
}
