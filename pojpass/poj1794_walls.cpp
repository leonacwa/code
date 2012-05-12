#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 30000 * 2 + 100;
typedef long long llong;

struct Node {
	int x, y;
};
bool cmpyx(const Node &A, const Node &B) {
	if (A.y != B.y) return A.y < B.y;
	return A.x > B.x;
}

Node A[MAXN];
Node tA[MAXN];

llong merge_sort(Node A[], int n)
{
	if (n <= 1) return 0;
	int mi = (n - 1) / 2;
	llong res = 0;
	res += merge_sort(A, mi + 1);
	res += merge_sort(A + mi + 1, n - mi - 1);
	int a = 0, b = mi + 1, l = 0;
	while (a <= mi && b < n) {
		if (A[a].x > A[b].x) {
			tA[l++] = A[b++];
			res += mi - a + 1;
		} else {
			tA[l++] = A[a++];
		}
	}
	while (a <= mi) {
		tA[l++] = A[a++];
	}
	while (b < n) {
		tA[l++] = A[b++];
	}
	for (int i = 0; i < n; ++i) {
		A[i] = tA[i];
	}
	return res;
}

int main()
{
	int nTest, nCase = 0;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n + m; ++i) {
			scanf("%d %d", &A[i].x, &A[i].y);
		}
		llong ans = 0;

		sort(A, A + n, cmpyx);
		ans -= merge_sort(A, n);

		sort(A + n, A + n + m, cmpyx);
		ans -= merge_sort(A + n, m);

		sort(A, A + n + m, cmpyx);
		ans += merge_sort(A, n + m);

		printf("Scenario #%d:\n", ++nCase);
		printf("%lld\n\n", ans);
	}
	return 0;
}

