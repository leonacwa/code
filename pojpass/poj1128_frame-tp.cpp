#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 26;
const int HW = 31;
const char npos = '.';
struct Card {
	int x1, y1, x2, y2;
};
struct String {
	char s[NN+1];
};
bool cmpStr (const String &a, const String &b) {
	return strcmp(a.s, b.s) < 0;
}

int h, w;
int cnt;
Card c[NN];
int order[NN];
int ind[NN];
bool used[NN];
char mat[HW][HW];
bool ma[HW][HW];
int ans_cnt;
char str[NN+1];
String ans[NN*NN];

void dfs(int remain)
{
	if (remain == 0) {
		strcpy(ans[ans_cnt].s, str);
		ans_cnt++;
		return;
	}
	for (int i = 0; i < cnt; ++i) {
		int now = order[i];
		if (used[now] || ind[now] != 0) continue;
		for (int j = 0; j < cnt; ++j) {
			int nxt = order[j];
			if (nxt != now && ma[now][nxt]) {
				--ind[nxt];
			}
		}
		used[now] = true;
		str[remain - 1] = now + 'A';
		dfs(remain - 1);
		used[now] = false;
		for (int j = 0; j < cnt; ++j) {
			int nxt = order[j];
			if (nxt != now && ma[now][nxt]) {
				++ind[nxt];
			}
		}
	}
}

int main()
{
	while (EOF != scanf("%d %d", &h, &w)) {
		for (int i = 0; i < NN; ++i) {
			c[i].x1 = c[i].y1 = INT_MAX;
			c[i].x2 = c[i].y2 = -1;
		}
		for (int i = 0; i < h; ++i) {
			scanf("%s", mat[i]);
			for (int j = 0; j < w; ++j) {
				if (mat[i][j] == npos) continue;
				int k = mat[i][j] - 'A';
				c[k].x1 = min(c[k].x1, i);
				c[k].y1 = min(c[k].y1, j);
				c[k].x2 = max(c[k].x2, i);
				c[k].y2 = max(c[k].y2, j);
			}
		}
		memset(ma, 0, sizeof(ma));
		memset(ind, 0, sizeof(ind));
		cnt = 0;
		for (int i = 0; i < NN; ++i) {
			if (c[i].x2 > -1) {
				order[cnt++] = i;
				int x1 = c[i].x1, y1 = c[i].y1, x2 = c[i].x2, y2 = c[i].y2;
				char ch = i + 'A';
				for (int x = x1; x <= x2; ++x) {
					if (mat[x][y1] != ch && !ma[mat[x][y1] - 'A'][i]) {
						ma[mat[x][y1] - 'A'][i] = true;
						++ind[i];
					}
					if (mat[x][y2] != ch && !ma[mat[x][y2] - 'A'][i]) {
						ma[mat[x][y2] - 'A'][i] = true;
						++ind[i];
					}
				}
				for (int y = y1; y <= y2; ++y) {
					if (mat[x1][y] != ch && !ma[mat[x1][y] - 'A'][i]) {
						ma[mat[x1][y] - 'A'][i] = true;
						++ind[i];
					}
					if (mat[x2][y] != ch && !ma[mat[x2][y] - 'A'][i]) {
						ma[mat[x2][y] - 'A'][i] = true;
						++ind[i];
					}
				}
			}
		}
		memset(used, 0, sizeof(used));
		ans_cnt = 0;
		str[cnt] = 0;
		dfs(cnt);
		sort(ans, ans + ans_cnt, cmpStr);
		for (int i = 0; i < ans_cnt; ++i) {
			puts(ans[i].s);
		}
	}
	return 0;
}

