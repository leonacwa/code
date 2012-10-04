/*
 * HDU 4400 Mines
 * */
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

struct Point {
	int x, y;
	int d;
	int e;
};


struct cmpY {
	bool operator () (const Point &a, const Point &b) const {
		return a.y < b.y;
	}
};

typedef multiset<Point, cmpY> MSPY;
typedef map<int, MSPY> MIS;

Point p[MAXN];
bool is_e[MAXN];

int dis(const Point &a, const Point &b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

int main() {
	int n, ca = 0;
	while (EOF != scanf("%d", &n) && n > 0) {
		++ca;
		MIS mx;
		for (int i = 0; i < n; ++i) {
			int x, y, d;
			scanf("%d%d%d", &x, &y, &d);
			p[i].x = x, p[i].y = y, p[i].d = d;
			p[i].e = i;
			is_e[i] = false;
			mx[ p[i].x ].insert(p[i]);
		}
		int m, k, ans;
		scanf("%d", &m);
		printf("Case #%d:\n", ca);
		while (m--) {
			scanf("%d", &k);
			--k;
			//printf("q %d\n", k);
			ans = 0;
			if (!is_e[ p[k].e ]) {
				queue<Point> que;
				que.push(p[k]);
				while (!que.empty()) {
					Point p = que.front();
					que.pop();
					if (is_e[p.e]) continue;
					is_e[p.e] = true;
					++ans;
					//printf("bfs %d %d\n", p.x, p.y);
					if (mx.empty()) continue;
					int lo = p.x - p.d, hi = p.x + p.d;
					MIS::iterator mit = mx.lower_bound(lo);
					for (; mit != mx.end() && mit->first <= hi; ++mit) {
						if (mit->second.empty()) continue;
						Point py = p;
						py.y -= p.d;
						MSPY::iterator sit = mit->second.lower_bound(py);
						py.y = p.y + p.d;
						for (; sit != mit->second.end() && sit->y <= py.y; ) {
							if (dis(*sit, p) <= p.d) {
								if (!is_e[sit->e]) que.push(*sit);
								MSPY::iterator sit2 = sit++;
								mit->second.erase(sit2);
							} else {
								++sit;
							}
						}
					}
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
