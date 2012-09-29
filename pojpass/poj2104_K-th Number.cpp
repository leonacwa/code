/* poj 2104 K-th Number
 * 线段树+二分答案，也就是二分哪一个位置是区间内的第k个数
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int *p[MAXN*2];
int cnt;
int a[MAXN*20];

#define rt ((L+R)|(L!=R))
#define lson ((L+M)|(L!=M))
#define rson ((M+1+R)|(M+1!=R))

void merge(int a[], int la, int b[], int lb, int c[]) {
	int i = 0, j = 0, k = 0;
	while (i < la && j < lb) {
		if (a[i] < b[j]) c[k++] = a[i++];
		else c[k++] = b[j++];
	}
	while (i < la) c[k++] = a[i++];
	while (j < lb) c[k++] = b[j++];
}

void make_tree(int L, int R) {
	if (L == R) {
		scanf("%d", &a[cnt]);
		p[rt] = a + cnt++;
		return;
	}
	if (L > R) return;
	int M = (L+R)>>1;
	make_tree(L, M);
	make_tree(M+1, R);
	p[rt] = a + cnt;
	cnt += R - L + 1;
	merge(p[lson], M+1-L, p[rson], R-M, p[rt]);
}

int query_k(int L, int R, int l, int r, int x) {
	if (l <= L && R <= r) {
		int a = 0, b = R - L, m;
		while (a < b) {
			m = (a+b)>>1;
			if (p[rt][m] < x) a = m + 1;
			else b = m;
		}
		return p[rt][a] <= x ? a+1 : a;
	}
	if (L >= R) return 0;
	int M = (L+R)>>1;
	int res = 0;
	if (l <= M) res += query_k(L, M, l, r, x);
	if (M < r) res += query_k(M+1, R, l, r, x);
	return res;
}

int query(int L, int R, int l, int r, int k) {
	int a = 0, b = R - L, m;
	/* 二分第k个数 */
	while (a < b) {
		m = (a+b)>>1;
		if ( query_k(L, R, l, r, p[rt][m]) < k) {
			a = m + 1;
		} else {
			b = m;
		}
	}
	return p[rt][a];
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		cnt = 0;
		make_tree(1, n);
		while (m--) {
			int i, j, k;
			scanf("%d%d%d", &i, &j, &k);
			printf("%d\n", query(1, n, i, j, k));
		}
	}
	return 0;
}
