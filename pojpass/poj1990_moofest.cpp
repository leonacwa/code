#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 20000 + 10;
typedef long long llong;

struct Node {
	int v, x;
	bool operator < (const Node &B) const {
		return v < B.v;
	}
} node[MAXN];

int lowbit(int x) {
	return x & -x;
}

void add(llong C[], int x, llong val) {
	for (; x < MAXN; x += lowbit(x)) {
		C[x] += val;
	}
}

llong sum(llong C[], int x) {
	llong ret = 0;
	for (; x > 0; x -= lowbit(x)) {
		ret += C[x];
	}
	return ret;
}

llong Count[MAXN];
llong Total[MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &node[i].v, &node[i].x);
		}
		sort(node, node + n);
		llong ans = 0, allTotal = 0;
		memset(Count, 0, sizeof(Count));
		memset(Total, 0, sizeof(Total));
		for (int i = 0; i < n; ++i) {
			int x = node[i].x;
			llong count = sum(Count, x - 1);
			llong total = sum(Total, x - 1);
			ans += (count * x - total + allTotal - total - (i - count) * x) * node[i].v;
			allTotal += node[i].x;
			add(Count, x, 1);
			add(Total, x, x);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

