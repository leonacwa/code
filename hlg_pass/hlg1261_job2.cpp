#include <cstdio>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

const int NN = 100000 + 5;
struct Node {
	int d, v;
	bool operator < (const Node &B) const {
		if (d != B.d) return d < B.d;
		return v > B.v;
	}
};
Node ap[NN];
int n, m;
int A[NN*2];

int main()
{
	while (EOF != scanf("%d %d", &n, &m)) {
		for (int i = 0; i < n; ++i) {
			int d, v;
			scanf("%d %d", &d, &v);
			if (d > m) d = m;
			ap[i].d = d;
			ap[i].v = v;
		}
		sort(ap, ap+n);
		int t = 0;
		int ans = 0;
		int nA = 0;
		make_heap(A, A+nA, greater<int>());
		for (int i = 0; i < n; ++i) {
			if (t < ap[i].d && t < m) {
				ans += ap[i].v;
				++t;
				A[nA++] = ap[i].v;
				push_heap(A, A+nA, greater<int>());
			} else if (nA > 0) {
				int v = A[0];
				if (v < ap[i].v) {
					ans += ap[i].v - v;
					pop_heap(A, A+nA, greater<int>());
					A[nA-1] = ap[i].v;
					push_heap(A, A+nA, greater<int>());
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

