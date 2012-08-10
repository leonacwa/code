#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 205;

struct Point {
	double x, y, v;
} pir[MAXN], ten[MAXN], cap, head;

struct Node {
	double d;
	int n, p;
	bool operator < (const Node& B) const {
		return d < B.d;
	}
} nd[MAXN*MAXN];

int match[MAXN];
bool mat[MAXN][MAXN], mk[MAXN];

double dist(Point p1, Point p2) {
	double x = p1.x - p2.x, y = p1.y - p2.y;
	return sqrt(x * x + y * y);
}

bool dfs(bool mat[][MAXN], int n, int x)
{
    for (int i = 0; i < n; i++){
        if (mat[x][i] && !mk[i]){
            mk[i] = true;
            if (match[i] == -1 or dfs(mat, n, match[i])){
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

int hungary(bool mat[][MAXN], int n)
{
    int ret = 0;
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; i++){
        memset(mk, false, sizeof(mk));
        mk[i] = true;
        ret += dfs(mat, n, i) ? 1 : 0;
    }
    return ret;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, p;
		int x, y, v;
		scanf("%d%d", &n, &p);
		scanf("%d%d%d", &x, &y, &v);
		cap.x = x, cap.y = y, cap.v = v;
		for (int i = 0; i < p; ++i) {
			scanf("%d%d%d", &x, &y, &v);
			pir[i].x = x, pir[i].y = y, pir[i].v = v;
		}
		scanf("%d%d", &x, &y);
		head.x = x, head.y = y, head.v = v;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &x, &y);
			ten[i].x = x, ten[i].y = y, ten[i].v = v;
		}
		int tot = 0;
		for (int i = 0; i < p; ++i) {
			for (int j = 0; j < n; ++j) {
				nd[tot].d = dist(pir[i], ten[j]) / pir[i].v;
				nd[tot].p = i, nd[tot].n = j;
				++tot;
			}
		}
		sort(nd, nd + tot);
		/*
		for (int i = 0; i < tot; ++i) {
			printf("%lf %d %d\n", nd[i].d, nd[i].p, nd[i].n);
		}
		*/
		int l = 0, r = tot - 1, m;
		while (l < r) {
			m = (l + r) >> 1;
			memset(mat, 0, sizeof(mat));
			for (int i = 0; i <= m; ++i) {
				mat[nd[i].p][nd[i].n + p] = true;
				//mat[nd[i].n + p][nd[i].p] = true;
			}
			if (hungary(mat, p + n) == n) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		m = l;
		//printf("test %f %f\n", dist(cap, head) / cap.v , nd[m].d);
		double ans = dist(cap, head) / cap.v + nd[m].d;
		printf("%.9lf\n", ans);
	}
	return 0;
}
