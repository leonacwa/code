#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
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
		priority_queue<int, vector<int>, greater<int> > Q;
		for (int i = 0; i < n; ++i) {
			if (t < ap[i].d && t < m) {
				ans += ap[i].v;
				++t;
				Q.push(ap[i].v);
			} else {
				if (!Q.empty()) {
					int v = Q.top();
					if (v < ap[i].v) {
						Q.pop();
						ans += ap[i].v - v;
						Q.push(ap[i].v);
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

