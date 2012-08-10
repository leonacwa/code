#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 100005;
struct Point {
	int x, y, i;
} pt[MAXN];

bool cmpx(const Point a, const Point b) {
	return a.x < b.x;
}

bool cmpy(const Point a, const Point b) {
	return a.y < b.y;
}
int64 ld[MAXN], rd[MAXN], ud[MAXN], dd[MAXN];

int main()
{
	int runs;
	int n, pre, now;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &pt[i].x, &pt[i].y);
			pt[i].i = i;
		}
		sort(pt, pt + n, cmpx);
		pre = pt[0].i;
		ld[pre] = 0;
		for (int i = 1; i < n; ++i) {
			now = pt[i].i;
			ld[now] = ld[pre] + (int64)i * abs(pt[i].x - pt[i-1].x);
			pre = now;
		}
		pre = pt[n-1].i;
		rd[pre] = 0;
		for (int i = n - 2; i >= 0; --i) {
			now = pt[i].i;
			rd[now] = rd[pre] + (int64)(n - i - 1) * abs(pt[i].x - pt[i+1].x);
			pre = now;
		}
		sort(pt, pt + n, cmpy);
		pre = pt[0].i;
		dd[pre] = 0;
		for (int i = 1; i < n; ++i) {
			now = pt[i].i;
			dd[now] = dd[pre] + (int64)i * abs(pt[i].y - pt[i-1].y);
			pre = now;
		}
		pre = pt[n-1].i;
		ud[pre] = 0;
		for (int i = n - 2; i >= 0; --i) {
			now = pt[i].i;
			ud[now] = ud[pre] + (int64)(n - i - 1) * abs(pt[i].y - pt[i+1].y);
			pre = now;
		}
		int64 ans = -1ULL>>1, t;
		for (int i = 0; i < n; ++i) {
			t = ld[i] + rd[i] + ud[i] + dd[i];
			if (ans > t) ans = t;
		}
		printf("%lld\n", ans);
		//printf("%I64d\n", ans);
	}
	return 0;
}

