#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int h[MAXN][MAXN];
int c[MAXN][MAXN];
int R, C;
int ans;
int cnt;
struct Point {
	int x, y, h;
	bool operator < (const Point&b ) const {
		return h < b.h;
	}
};;
Point pt[MAXN*MAXN];

int main()
{
	while (EOF != scanf("%d %d", &R, &C)) {
		cnt = 0;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf("%d", &h[i][j]);
				pt[cnt].x = i;
				pt[cnt].y = j;
				pt[cnt].h = h[i][j];
				cnt++;
			}
		}
		sort(pt, pt+cnt);
		memset(c, 0, sizeof(c));
		for (int k = 0; k < cnt; k++) {
			int x = pt[k].x, y = pt[k].y;
			for (int i = 0; i < 4; i++) {
				int xt = x + d[i][0], yt = y + d[i][1];
				if (0 <= xt && xt < R && 0 <= yt && yt < C && h[x][y] < h[xt][yt]) {
					c[xt][yt] = max(c[xt][yt], c[x][y]+1);
				}
			}
		}
		ans = 0;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				ans = max(ans, c[i][j]);
			}
		}
		printf("%d\n", ans+1);
	}
	return 0;
}

