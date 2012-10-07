/* Graham-Scan 求凸包 + 旋转卡壳法求凸多边形最大直径
 * O(n*logn)
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long llong;
const int MAXN = 30000 + 10;
struct Point {
	llong x, y;
};

llong dist2(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

llong cross(const Point &A, const Point &B, const Point &C)
{
	return (A.x - C.x) * (B.y - C.y) - (A.y - C.y) * (B.x - C.x);
}
Point base; // 极角排序的基点
bool cmp(const Point &A, const Point &B) {
	llong ret = cross(A, B, base);
	if (ret != 0) return ret > 0;
	return dist2(A, base) < dist2(B, base);
}

int graham(int n, Point pt[], int st[]) {
	if (n <= 2) return n;
	int p = 0;
	for (int i = 1; i < n; ++i) {
		if (pt[p].y > pt[i].y || (pt[p].y == pt[i].y && pt[p].x > pt[i].x)) {
			p = i;
		}
	}
	swap(pt[0], pt[p]);
	base = pt[0];
	sort(pt + 1, pt + n, cmp);
	int top = -1;
	st[++top] = 0;
	st[++top] = 1;
	for (int i = 2; i < n; ++i) {
		while (top > 0 && cross(pt[i], pt[st[top]], pt[st[top-1]]) >= 0) --top;
		st[++top] = i;
	}
	for (int i = 0; i <= top; ++i) pt[i] = pt[st[i]];
	return top + 1;
}

llong rotating_calipers(int n, Point pt[])
{
	int q = 1;
	llong ans = 0;
	for (int p = 0; p < n; ++p) {
		int lp = (p + 1) % n;
		int lq = (q + 1) % n;
		while (cross(pt[lp], pt[lq], pt[p]) > cross(pt[lp], pt[q], pt[p])) {
			q = lq;
			lq = (q + 1) % n;
		}
		ans = max(ans, max(dist2(pt[p], pt[q]), dist2(pt[p], pt[lq])));
	}
	return ans;
}

int st[MAXN];
Point pt[MAXN];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lld %lld", &pt[i].x, &pt[i].y);
			//printf("%lld %lld\n", pt[i].x, pt[i].y);
		}
		int s = graham(n, pt, st);
		llong ans = rotating_calipers(s, pt);
		printf("%lld\n", ans);
	}
	return 0;
}

