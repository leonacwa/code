/* HDU4417 Super Mario
 * 划分树，类似归并排序的方式建树，nlogn时间复杂度，每个节点保存一个有序数组的指针
 * 查询：二分查找区间，查找范围在这个节点对应的区间内，则二分判断小于等于查询的数的个数
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int *pa[MAXN<<2];
int tot;
int ma[(MAXN<<2) * 17];

int bin(int a[], int na, int x) {
	if (x > a[na-1]) return na - 1;
	if (x < a[0]) return -1;
	int l = 0, r = na - 1, m;
	while (l < r-1) {
		m = (l + r) >> 1;
		if (x < a[m]) {
			r = m - 1;
		} else {
			l = m;
		}
	}
	if (a[r] <= x) return r;
	if (a[l] <= x) return l;
	return -1;
}

void merge(int a[], int na, int b[], int nb, int c[]) {
	int i = 0, j = 0, nc = 0;
	while (i < na && j < nb) {
		if (a[i] < b[j]) {
			c[nc++] = a[i++];
		} else {
			c[nc++] = b[j++];
		}
	}
	while (i < na) c[nc++] = a[i++];
	while (j < nb) c[nc++] = b[j++];
}

#define lson (rt<<1)
#define rson (rt<<1|1)

void make_tree(int rt, int L, int R) {
	if(L == R) {
		scanf("%d", &ma[tot]);
		pa[rt] = ma + tot++;
		return;
	}
	int M = (L + R) >> 1;
	make_tree(lson, L, M);
	make_tree(rson, M + 1, R);
	pa[rt] = ma + tot;
	tot += R - L + 1;
	merge(pa[lson], M-L+1, pa[rson], R-M, pa[rt]);
}

int query(int rt, int L, int R, int l, int r, int h) {
	if (l <= L && R <= r) {
		return 1 + bin(pa[rt], R - L + 1, h);
	}
	if (L >= R) return 0;
	int M = (L + R) >> 1;
	int ret = 0;
	if (l <= M) ret += query(lson, L, M, l, r, h);
	if (M < r) ret += query(rson, M+1, R, l, r, h);
	return ret;
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int ca = 1; ca <= runs; ++ca) {
		int n, m;
		scanf("%d%d", &n, &m);
		tot = 0;
		make_tree(1, 0, n-1);
		printf("Case %d:\n", ca);
		for (int i = 0; i < m; ++i) {
			int a, b, h;
			scanf("%d%d%d", &a, &b, &h);
			if (a > b) swap(a, b);
			printf("%d\n", query(1, 0, n-1, a, b, h));
		}
	}
	return 0;
}
