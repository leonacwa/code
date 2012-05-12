#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

const int NN = 100;
const int MAX_ANS = 2000;
struct Str{
	char s[NN];
	bool operator < (const Str &b) const {
		return strcmp(s, b.s) < 0;
	}
};

char sa[NN], sb[NN];
int la, lb, ll;
int f[NN][NN];
char str[NN];
int lsta[NN][26], lstb[NN][26];
Str ans[MAX_ANS], S;
int cnt;

void deal(const char *s, int ls, int last[][26])
{
	memset(last, 0, sizeof(last[0][0])*(ls+1)*26);
	for (int i = 1; i <= ls; ++i) {
		for (int j = 0; j < 26; ++j) {
			if (s[i] == 'a'+j) {
				last[i][j] = i;
			} else {
				last[i][j] = last[i-1][j];
			}
		}
	}
}

void find(int k, int l1, int l2)
{
	if (k <= 0) {
		ans[cnt++] = S;
		return;
	}
	for (int j = 0; j < 26; ++j) {
		int t1 = lsta[l1][j];
		int t2 = lstb[l2][j];
		if (f[t1][t2] == k) {
			S.s[k-1] = 'a' + j;
			find(k-1, t1-1, t2-1);
		}
	}
}

int main()
{
	while (EOF != scanf("%s%s", sa+1, sb+1)) {
		la = strlen(sa+1);
		lb = strlen(sb+1);
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= la; ++i) {
			for (int j = 1; j <= lb; ++j) {
				f[i][j] = max(f[i-1][j], f[i][j-1]);
				if (sa[i] == sb[j] && f[i][j] < 1 + f[i-1][j-1]) {
					f[i][j] = 1 + f[i-1][j-1];
				}
			}
		}
		deal(sa, la, lsta);
		deal(sb, lb, lstb);
		cnt = 0;
		ll = f[la][lb];
		S.s[ll] = 0;
		find(ll, la, lb);
		sort(ans, ans+cnt);
		for (int i = 0; i < cnt; ++i) {
			printf("%s\n", ans[i].s);
		}
	}
	return 0;
}

