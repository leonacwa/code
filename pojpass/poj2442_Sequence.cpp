/*
 * POJ 2442 Sequence
 * 堆的应用
 * */
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2005, MAXM = 105;
int a[2][MAXN];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, m;
		scanf("%d%d", &m, &n);
		for (int i = 0; i < n; ++i) scanf("%d", a[0] + i);
		make_heap(a[0], a[0] + n);
		int q = 0;
		for (int h = 1; h < m; ++h, q = 1-q) {
			int t;
			scanf("%d", &t);
			for (int i = 0; i < n; ++i) a[1-q][i] = a[q][i] + t;
			for (int i = 1; i < n; ++i) {
				scanf("%d", &t);
				for (int j = 0; j < n; ++j) {
					int t2 = a[q][j] + t;
					if (t2 < a[1-q][0]) {
						pop_heap(a[1-q], a[1-q] + n);
						a[1-q][n-1] = t2;
						push_heap(a[1-q], a[1-q] + n);
					}
				}
			}
		}
		sort(a[q], a[q] + n);
		for (int i = 0; i < n-1; ++i) {
			printf("%d ", a[q][i]);
		}
		printf("%d\n", a[q][n-1]);
	}
	return 0;
}
