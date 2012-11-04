/* CF 241 C. Mirror Box
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

const int MAXN = 105;

struct Point {
	LL x, y;
	Point() {}
	Point(int tx, int ty) : x(tx), y(ty) {}
};
LL cross(Point p2, Point p1, Point p0) {
	return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
}
bool isSegInter(Point p1, Point p2, Point q1, Point q2) {
	return (
			min(p1.x, p2.x) <= max(q1.x, q2.x) &&
			min(q1.x, q2.x) <= max(p1.x, p2.x) &&
			min(p1.y, p2.y) <= max(q1.y, q2.y) &&
			min(q1.y, q2.y) <= max(p1.y, p2.y) && /* 跨立实验 */
			cross(p1, q2, q1) * cross(p2, q2, q1) <= 0 && 
			cross(q1, p2, p1) * cross(q2, p2, p1) <= 0  /* 叉积相乘判方向 */
		   );
}

struct Mirror {
	int a, b, v;
} mi[2][MAXN];
int li[2], hl, hr, n;

int isInter(Point p1, Point p2, Mirror mi[], int li, int y, bool vi[]) {
	for (int i = 0; i < li; ++i) {
		if (!vi[i] &&  isSegInter(p1, p2, Point(mi[i].a, y), Point(mi[i].b, y)) ) {
			vi[i] = 1;
			return mi[i].v;
		}
	}
	return 0;
}

int check(int k, int ne) {
	int ret = 0;
	int hr2 = k * 100 + (k%2 ? 100-hr : hr);
	Point pl(0, hl), pr(100000, hr2);
	bool vi[2][MAXN];
	memset(vi, 0, sizeof(vi));
//	int ans[MAXN], cnt = 0;
	for (int i = 0; i < k; ++i) {
		int t = isInter(pl, pr, mi[(i+ne)%2], li[(i+ne)%2], 100*i + 100, vi[(i+ne)%2]);
		if (t == 0) return 0;
	//	ans[cnt++] = t;
		ret += t;
	}
//	printf("%d %d %d:", k, ne, cnt);for (int i = 0; i < cnt; ++i) printf(" %d", ans[i]); puts("");
	return ret;
}

int main() {
	while (EOF != scanf("%d%d%d", &hl, &hr, &n)) {
		li[0] = li[1] = 0;
		for (int i = 0; i < n; ++i) {
			char s[4];
			int v, a, b, j;
			scanf("%d%s%d%d", &v, s, &a, &b);
			j = (s[0] == 'T' ? 0 : 1);
			mi[j][li[j]].v = v;
			mi[j][li[j]].a = a;
			mi[j][li[j]].b = b;
			++li[j];
		}
		int ans = 0;
		for (int ne = 0; ne <= 1; ++ne) {
			for (int k = 1; k <= n; ++k) {
				int t = check(k, ne);
				if (t > ans) ans = t;
			}
			hl = 100 - hl;
			hr = 100 - hr;
		}
		printf("%d\n", ans);
	}
	return 0;
}
