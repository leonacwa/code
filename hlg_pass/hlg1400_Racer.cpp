#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long llong;

const int MAXN = 100005;
struct Node {
	int x, v;
};

bool cmpxv(const Node &A, const Node &B) {
	if (A.x != B.x) return A.x > B.x;
	return A.v < B.v;
}

Node tmp[MAXN];
llong merget_sort(Node A[], int n)
{
	if (n <= 1) return 0;
	int m = (n - 1) / 2;
	llong ret = 0;
	ret += merget_sort(A, m + 1);
	ret += merget_sort(A + m + 1, n - m - 1);
	int a = 0, b = m + 1, l = 0;
	while (a <= m && b < n) {
		if (A[b].v > A[a].v) {
			tmp[l++] = A[b++];
			ret += m - a + 1;
		} else {
			tmp[l++] = A[a++];
		}
	}
	while (a <= m) {
		tmp[l++] = A[a++];
	}
	while (b < n) {
		tmp[l++] = A[b++];
	}
	for (int i = 0; i < n; ++i) {
		A[i] = tmp[i];
	}
	return ret;
}

Node pt[MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &pt[i].x, &pt[i].v);
		}
		sort(pt, pt + n, cmpxv);
		llong ans = merget_sort(pt, n);
		printf("%lld\n", ans);
	}
	return 0;
}

