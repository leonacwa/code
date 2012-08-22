/*
¼«½ÇÅÅÐò
1318
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int NN = 100;
struct Point {
	int x, y, id;
};

Point ap[NN];
Point ans[NN];
int cnt;
bool used[NN];

int xmult(const Point &A, const Point &B, const Point& C)
{
	return (A.x - C.x) * (B.y - C.y) - (A.y - C.y) * (B.x - C.x);
}

int dist(const Point &A, const Point &B)
{
	return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, d = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d", &ap[i].id, &ap[i].x, &ap[i].y);
			if (ap[d].y > ap[i].y || (ap[d].y == ap[i].y && ap[d].x > ap[i].x)) {
				d = i;
			}
		}
		memset(used, 0, sizeof(used));
		cnt = 1;
		ans[0].x = 0, ans[0].y = ap[d].y;
		ans[1] = ap[d];
		used[ap[d].id] = true;
		while (1) {
			int first = 1;
			for (int i = 0; i < n; ++i) {
				if (!used[ap[i].id]) {
					if (xmult(ap[i], ans[cnt], ans[cnt-1]) <= 0) {
						if (first) {
							d = i;
							first = 0;
						} else {
							int t = xmult(ap[i], ap[d], ans[cnt]);
							if (t > 0 || ( t == 0 && dist(ap[i], ans[cnt]) < dist(ap[d], ans[cnt]))) {
								d = i;
							}
						}
					}
				}
			}
			if (first) break;
			ans[++cnt] = ap[d];
			used[ap[d].id] = true;
		}
		printf("%d", cnt);
		for (int i = 1; i <= cnt; ++i) {
			printf(" %d", ans[i].id);
		}
		puts("");
	}
	return 0;
}

