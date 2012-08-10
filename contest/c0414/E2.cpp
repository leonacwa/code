// WA
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 205;
typedef long long LLONG;
struct Point {
	char t;
	LLONG x, y;
};

LLONG xmult(const Point &p2, const Point &p1, const Point &p0) {
	return (p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y);
}

Point bp;
bool cmpangle(const Point &a, const Point &b) { // true clockwise, fl=alse counterclockwise
	return (a.x - bp.x) * (b.y - bp.y) - (a.y - bp.y) * (b.x - bp.x) > 0;
}

Point p[NN*2], pp[NN*2];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, m, nm;
		scanf("%d %d", &n, &m);
		nm = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%lld %lld", &p[nm].x, &p[nm].y);
			p[nm].t = 'l';
			++nm;
		}
		for (int i = 0; i < m; ++i) {
			scanf("%lld %lld", &p[nm].x, &p[nm].y);
			p[nm].t = 'u';
			++nm;
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			int cnt = nm - i - 1;
			if (cnt < 2) break;
			memcpy(pp, p+i+1, sizeof(p[0])*cnt);
			bp = p[i];
			sort(pp, pp + cnt, cmpangle);
			for (int j = 0; j < cnt; ++j) {
				if (pp[j].t != 'l') continue;
				Point minC;
				minC.t = 0;
				for (int k = (j + 1) % cnt; k != j; k = (k + 1) % cnt) {
				//for (int k = j + 1; k < cnt; ++k) {
					if (xmult(pp[k], pp[j], bp) >= 0) break;
					if (pp[k].t == 'l') {
						if (minC.t != 'u' || xmult(pp[k], minC, pp[j]) < 0) {
							++ans;
						}
					} else {
						if (minC.t != 'u' || xmult(pp[k], minC, pp[j]) < 0) {
							minC = pp[k];
						}
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

