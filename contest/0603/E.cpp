#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 15;

int n, Max;
int dom[MAXN][2];
struct Dom {int l, r; } rdom[MAXN];
int M[MAXN][MAXN][2];
bool used[MAXN];

bool can(int d, int x, int y, int z)
{
	if (M[x][y][z]) return false;
	bool ret = false;
	if (z == 0) {
		ret = (M[x][y-1][1] == d || M[x-1][y][1] == d || M[x][y][1] == d) &&
			((M[x][y-1][1] == d || M[x][y-1][1] == 0) && (M[x-1][y][1] == d || M[x-1][y][1] == 0) &&
			 (M[x][y][1] == d || M[x][y][1] == 0));
	} else {
		ret = (M[x][y][0] == d || M[x+1][y][0] == d || M[x][y+1][0] == d) &&
			((M[x][y][0] == d || M[x][y][0] == 0) && (M[x+1][y][0] == d || M[x+1][y][0] == 0) &&
			 (M[x][y+1][0] == d || M[x][y+1][0] == 0));
	}
	return ret;
}

int count(int d, int x, int y, int z)
{
	if (M[x][y][z] != d) return 0;
	int ret = 0;
	if (z == 0) {
		ret = (M[x][y-1][1] == d) + (M[x-1][y][1] == d)  + (M[x][y][1] == d);
	} else {
		ret = (M[x][y][0] == d) + (M[x+1][y][0] == d) + (M[x][y+1][0] == d);
	}
	return ret;
}
bool test(int x, int y, int z)
{
	bool ret = false;
	if (z == 0) {
		ret = ((M[x][y-1][1] == 0) && (M[x-1][y][1] == 0) &&
				(M[x][y][1] == 0));
	} else {
		ret = ((M[x][y][0] == 0) && (M[x+1][y][0] == 0) &&
				(M[x][y+1][0] == 0));
	}
	return ret;
}

struct XY {
	int x, y, z;
} xy[MAXN][MAXN*MAXN];
int cnt[MAXN];

bool mat[MAXN][MAXN][2];

void dfs_xy(XY xy[], int &cnt, int x, int y, int z)
{
	if (x <= 0 || x >= MAXN || y <= 0 || y >= MAXN) return;
	if (mat[x][y][z]) return;
	mat[x][y][z] = true;
	if (M[x][y][z] == 0) {
		xy[cnt].x = x;
		xy[cnt].y = y;
		xy[cnt].z = z;
		++cnt;
		return;
	}
	int d = z ? 1 : -1;
	dfs_xy(xy, cnt, x, y, 1-z);
	dfs_xy(xy, cnt, x-1, y, 1-z);
	dfs_xy(xy, cnt, x, y-1, 1-z);
}

void dfs(int i, int sum)
{
	if (Max < sum) Max = sum;
	if (i > n) return;
	memset(mat, 0, sizeof(mat));
	cnt[i] = 0;
	dfs_xy(xy[i], cnt[i], MAXN/2, MAXN/2, 0);
	dfs_xy(xy[i], cnt[i], MAXN/2, MAXN/2, 1);
	for (int j = 0; j < cnt[i]; j++) {
	    int x = xy[i][j].x, y = xy[i][j].y, z = xy[i][j].z;
		if (M[x][y][0] && M[x][y][1]) continue;
		if (test(x, y, 0) && test(x, y, 1)) continue;
		int d = z ? 1 : -1;
		for (int k = 0; k < 2; ++k) {
			int a = dom[i][k], b = dom[i][1 - k];
			if (can(a, x, y, z)) {
				M[x][y][z] = b;
				if (can(b, x, y, 1-z)) {
					M[x][y][z] = a;
					M[x][y][1-z] = b;
					int t = count(a, x, y, z) + count(b, x, y, 1-z) - (a==b)*2;
					dfs(i+1, sum + t);
					M[x][y][z] = b;
					M[x][y][1-z] = 0;
				}
				if (can(b, x, y-1, 1-z)) {
					M[x][y][z] = a;
					M[x][y+d][1-z] = b;
					int t = count(a, x, y, z) + count(b, x, y+d, 1-z) - (a==b)*2;
					dfs(i+1, sum + t);
					M[x][y][z] = b;
					M[x][y+d][1-z] = 0;
				}
				if (can(b, x+d, y, 1-z)) {
					M[x][y][z] = a;
					M[x+d][y][1-z] = b;
					int t = count(a, x, y, z) + count(b, x+d, y, 1-z) - (a==b) * 2;
					dfs(i+1, sum + t);
					M[x][y][z] = b;
					M[x+d][y][1-z] = 0;
				}
				M[x][y][z] = 0;
			}
		}
	}
}

int main()
{
	//freopen("data.in", "r", stdin);
	int nCase = 0;
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &rdom[i].l, &rdom[i].r);
		}
		int a[MAXN] = {1, 2, 3, 4, 5, 6, 7, 8};
		memset(M, 0, sizeof(M));
		Max = 0;
		do {
			for (int i = 1; i <= n; ++i) {
				dom[i][0] = rdom[a[i-1]].l, dom[i][1] = rdom[a[i-1]].r;
			}
			int x, y;
			x = y = MAXN / 2;
			int i = 1;
			for (int k = 0; k < 2; ++k) {
				int a = dom[i][k], b = dom[i][1-k];
				for (int z = 0; z < 2; ++z) {
					int d = z ? 1 : -1;
					//1
					M[x][y][z] = a;

					M[x][y][1-z] = b;
					dfs(i+1, 0);
					M[x][y][1-z] = 0;
					//2
					M[x][y+d][1-z] = b;
					dfs(i+1, 0);
					M[x][y+d][1-z] = 0;
					//3
					M[x+d][y][1-z] = b;
					dfs(i+1, 0);
					M[x+d][y][1-z] = 0;

					M[x][y][z] = 0;
				}
			}
		} while (next_permutation(a, a+n));
		//printf("%2d:", ++nCase);
		printf("%d\n", Max);
	}
	return 0;
}
