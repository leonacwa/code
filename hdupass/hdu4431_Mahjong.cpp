/*
 * HDU 4431 Mahjong
 * Asia 2012 ACM-ICPC Tianjin A. Mahjong
 * */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

char mjs_t[5] = "mspc";
char mjs[39][3];
map<string, int> mj;

bool isKM(int ic[]) { /* 1m, 9m, 1p, 9p, 1s, 9s and all 7 character tiles.  */
	int c[14];
	memcpy(c, ic, sizeof(c));
	sort(c, c + 14);
	int a[37] = {0};
	for (int i = 0; i < 14; ++i) {
		++a[c[i]];
		if (a[c[i]] > 2) return false;
	}
	int cnt = 0;
	for (int i = 1; i <= 34; ++i) {
		if (a[i] > 0) {
			c[cnt++] = i;
		}
	}
	if (cnt != 13) return false;

	bool ret = (c[0] == 1 && c[1] == 9 && c[2] == 10 && c[3] == 18 && c[4] == 19 && c[5] == 27);
	if (ret) {
		for (int i = 6; i < 13; ++i) {
			if (c[i] != 28 + i - 6) {
				return false;
			}
		}
	}
	return ret;
}

bool isPair(int c[]) { /* 7 different pairs of tiles; */
	sort(c, c + 14);
	for (int i = 0; i < 14; i += 2) {
		if (c[i] == c[i+1] && (i == 0 || i > 0 && c[i-1] != c[i])) {
		} else return false;
	}
	return true;
}

bool same(int a, int b, int c) {
	int t = (a - 1) / 9;
	return (t == (b - 1) / 9) && (t == (c - 1) / 9);
}

bool isEye(int c[]) {
	sort(c, c + 14);
	int a[37] = {0};
	for (int i = 0; i < 14; ++i) {
		++a[c[i]];
	}
	for (int i = 0; i < 14; ++i) {
		if (a[c[i]] < 2 || (i > 0 && c[i-1] == c[i])) continue;
		int b[37];
		memcpy(b, a, sizeof(b));
		b[c[i]] -= 2;
		int cnt = 12;
		for (int j = 0; j < 14; ++j) {
			if (b[c[j]] == 0) continue;
			int x = c[j];
			if (b[x] >= 3) {
				b[x] -= 3;
				cnt -= 3;
			} else if (b[x] > 0 && x+2 <= 27 && b[x+1] > 0 && b[x+2] > 0 && same(x, x+1, x+2) ) {
				/* 东西南北白门发中没有顺子 */
				cnt -= 3;
				b[x]--;
				b[x+1]--;
				b[x+2]--;
			} else if (b[x] > 0) {
				break;
			}
			if (b[x] > 0) --j;
		}
		if (cnt == 0) {
			//printf("eye %s\n", mjs[c[i]]);
			return true;
		}
	}
	return false;
}

int main() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 1; j <= 9; ++j) {
			int k = i * 9 + j;
			mjs[k][0] = j + '0';
			mjs[k][1] = mjs_t[i];
			mjs[k][2] = 0;
			mj[mjs[k]] = k;
		}
	}
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int c[14];
		int ct[37] = {0};
		for (int i = 0; i < 13; ++i) {
			char str[4];
			scanf("%s", str);
			c[i] = mj[str];
			ct[c[i]]++;
		}
		int cnt = 0;
		int ans[37];
		for (int i = 1; i <= 34; ++i) {
			if (ct[i] == 4) continue;
			int b[14];
			memcpy(b, c, sizeof(c));
			b[13] = i;
			if (isPair(b) || isKM(b) || isEye(b)) {
				ans[cnt++] = i;
			}
		}
		if (cnt == 0) {
			puts("Nooten");
		} else {
			printf("%d", cnt);
			for (int i = 0; i < cnt; ++i) {
				printf(" %s", mjs[ans[i]]);
			}
			puts("");
		}
	}
	return 0;
}
