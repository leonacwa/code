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
bool used[NN];
char mat[HW][HW], mat2[HW][HW];
int ans_cnt;
char str[NN+1];
String ans[NN*NN];

void cover(char mat[HW][HW], const Card &c, const char ch)
{
	for (int x = c.x1; x <= c.x2; ++x) {
		if (mat[x][c.y1] == npos) {
			mat[x][c.y1] = ch;
		}
		if (mat[x][c.y2] == npos) {
			mat[x][c.y2] = ch;
		}
	}
	for (int y = c.y1; y <= c.y2; ++y) {
		if (mat[c.x1][y] == npos) {
			mat[c.x1][y] = ch;
		}
		if (mat[c.x2][y] == npos) {
			mat[c.x2][y] = ch;
		}
	}
}

void recover(char mat[HW][HW], const Card &c, const char ch)
{
	for (int x = c.x1; x <= c.x2; ++x) {
		if (mat[x][c.y1] == ch) {
			mat[x][c.y1] = npos;
		}
		if (mat[x][c.y2] == ch) {
			mat[x][c.y2] = npos;
		}
	}
	for (int y = c.y1; y <= c.y2; ++y) {
		if (mat[c.x1][y] == ch) {
			mat[c.x1][y] = npos;
		}
		if (mat[c.x2][y] == ch) {
			mat[c.x2][y] = npos;
		}
	}
}

bool check(const char mat[HW][HW], const char mat2[HW][HW], const Card &c)
{
	for (int x = c.x1; x <= c.x2; ++x) {
		if (mat[x][c.y1] != mat2[x][c.y1]) return false;
		if (mat[x][c.y2] != mat2[x][c.y2]) return false;
	}
	for (int y = c.y1; y <= c.y2; ++y) {
		if (mat[c.x1][y] != mat2[c.x1][y]) return false;
		if (mat[c.x2][y] != mat2[c.x2][y]) return false;
	}
	return true;
}

void dfs(int remain)
{
	if (remain == 0) {
		strcpy(ans[ans_cnt].s, str);
		ans_cnt++;
		return;
	}
	for (int i = 0; i < cnt; ++i) {
		if (used[i]) continue;
		cover(mat2, c[order[i]], order[i] + 'A');
		if (check(mat, mat2, c[order[i]])) {
	//		printf("%d:%c ", order[i], (char)(order[i] + 'A'));
			str[remain - 1] = order[i] + 'A';
			used[i] = true;
			dfs(remain - 1);
			used[i] = false;
		}
		recover(mat2, c[order[i]], order[i] + 'A');
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
		cnt = 0;
		for (int i = 0; i < NN; ++i) {
			if (c[i].x2 > -1) {
				order[cnt++] = i;
			}
		}
		memset(used, 0, sizeof(used));
		memset(mat2, npos, sizeof(mat2));
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

