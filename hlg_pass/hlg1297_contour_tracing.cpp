#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int NN = 200 + 5;
struct Point {
	int x, y;
	Point(int tx = 0, int ty = 0) : x(tx), y(ty)
	{}
	bool operator < (const Point& b) const {
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
	bool operator == (const Point& b) const {
		return x == b.x && y == b.y;
	}
};
const int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1}, dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int red[8] = {6, 6, 0, 0, 2, 2, 4, 4};

char mm[NN][NN];
int id[NN][NN], nid;
Point ap[NN*NN];
int nap;
int ans[NN*NN], nans;
int R, C;

int dfs(int x, int y, int nid)
{
	int i, tx, ty, ret = 1;
	id[x][y] = nid;
	for (i = 0; i < 8; ++i) {
		tx = x + dx[i], ty = y + dy[i];
		if (0 <= tx && tx < R && 0 <= ty && ty < C && mm[tx][ty] == '1' && id[tx][ty] == 0) {
			ret += dfs(tx, ty, nid);
		}
	}
	return ret;
}

int work(int x, int y)
{
	int i, j, ret = 0;
	Point n0, n1, n00, n11, nt, pn;
	n0.x = x, n0.y = y;
	for (i = 0; i < 8; ++i) {
		n1.x = n0.x + dx[i];
		n1.y = n0.y + dy[i];
		if (mm[n1.x][n1.y] == '1') {
			break;
		}
	}
	if (i == 8) return 1;
	n00 = n0, n11 = n1;
	n0 = n1;
	i = red[i];
	while (1) {
		for (j = 0; j < 8; ++j) {
			n1.x = n0.x + dx[(i+j) % 8];
			n1.y = n0.y + dy[(i+j) % 8];
			if (mm[n1.x][n1.y] == '1') {
				++ret;
				if (n00 == n0 && n11 == n1) {
					return ret;
				}
				n0 = n1;
				i = red[(i + j) % 8];
				//printf("go %d %d\n", n1.x, n1.y);
				break;
			}
		}
		while (j == 8) {
			printf("errorr\n");
		}
	}
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d", &R, &C) && R != 0 && C != 0) {
		nap = 0;
		for (int i = 0; i < R; ++i) {
			scanf("%s", mm[i]);
			for (int j = 0; j < C; j++) {
				if (mm[i][j] == '1') {
					ap[nap].x = i;
					ap[nap].y = j;
					++nap;
				}
			}
		}
		sort(ap, ap+nap);
		memset(id, 0, sizeof(id));
		nid = 0;
		nans = 0;
		for (int i = 0; i < nap; ++i) {
			if (id[ap[i].x][ap[i].y] == 0) {
				int ret = dfs(ap[i].x, ap[i].y, ++nid);
				if (ret >= 5) {
					ret = work(ap[i].x, ap[i].y);
					ans[nans++] = ret;
				}
			}
		}
		printf("Case %d\n", ++nCase);
		if (nans == 0) {
			puts("no objects found");
		} else {
			sort(ans, ans+nans);
			for (int i = 0; i < nans - 1; ++i) {
				printf("%d ", ans[i]);
			}
			printf("%d\n", ans[nans-1]);
		}
	}
	return 0;
}

