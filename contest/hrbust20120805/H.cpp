/* Obfuscation
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Word {
	char b, e;
	int cnt, id;
	int c[26];
};
bool cmpW(const Word &a, const Word &b) {
	for (int i = 0; i < 26; ++i) if (a.c[i] != b.c[i]) return a.c[i] < b.c[i];
	if (a.b != b.b) return a.b < b.b;
	return a.e < b.e;
}
int scmpW(const Word &a, const Word &b) {
	for (int i = 0; i < 26; ++i) if (a.c[i] != b.c[i]) return a.c[i] - b.c[i];
	if (a.b != b.b) return a.b - b.b;
	return a.e - b.e;
}

const int MAXN = 1005;

int n;
char str[MAXN], buf[10005][105];
int f[MAXN], opt[MAXN];
Word cnt[MAXN], wcnt[10005];

int find(const Word &w) {
	int l = 0, r = n - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		int ret = scmpW(w, wcnt[m]);
		if (ret == 0) return m;
		if (ret < 0) r = m -1;
		else l = m + 1;
	}
	return -1;
}

void print(int p) {
	if (p == 0) return;
	print(opt[p] - 1);
	if (opt[p] != 1) putchar(' ');
	printf("%s", buf[opt[p]]);
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%s", str+1);
		memset(cnt, 0, sizeof(Word));
		int ls = 0;
		for (int i = 1; str[i]; ++i) {
			++ls;
			cnt[i] = cnt[i-1];
			cnt[i].c[str[i]-'a']++;
		}
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			char * ch = buf[i];
			scanf("%s", ch);
			memset(wcnt+i, 0, sizeof(Word));
			wcnt[i].id = i;
			wcnt[i].cnt = 1;
			int j;
			for (j = 0; ch[j]; ++j) wcnt[i].c[ch[j]-'a']++;
			wcnt[i].b = ch[0];
			wcnt[i].e = ch[j-1];
		}
		sort(wcnt, wcnt + n, cmpW);
		int t = 0;
		for (int i = 1; i < n; ++i) {
			if (0 == scmpW(wcnt[t], wcnt[i])) {
				wcnt[t].cnt += wcnt[i].cnt;
			} else {
				wcnt[++t] = wcnt[i];
			}
		}
		n = t + 1;
		memset(f, 0, sizeof(f));
		memset(opt, -1, sizeof(opt));
		f[0] = 1;
		for (int i = 1; str[i]; ++i) {
			Word w = cnt[i];
			w.e = str[i];
			for (int j = 1; j <= i; ++j) {
				w.b = str[j];
				if (f[j-1] != 0) {
					int ret = find(w);
					if (ret != -1) {
						f[i] += wcnt[ret].cnt * f[j-1];
						opt[i] = wcnt[ret].id;
					}
				}
				w.c[str[j]-'a']--;
			}
		}
		if (f[ls] == 0) puts("impossible");
		else if (f[ls] > 1) {
			puts("ambiguous");
			/*
			printf("ambiguous  : ");
			print(ls);
			puts("");
			*/
		}
		else {
			print(ls);
			puts("");
		}
	}
	return 0;
}
