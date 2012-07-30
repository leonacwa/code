/* poj 3376 finding palindromes
 * Trie + Extend KMP
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 2100000;
char s0[MAXN], s1[MAXN];
int ext0[MAXN], ext1[MAXN], next[MAXN];
bool is0[MAXN], is1[MAXN];
int bg[MAXN], len[MAXN];

struct Node {
	int cnt, leaf;
	int ch[26];
} nd[MAXN];
int nNd;

void insert(int l, char s[], bool is[]) {
	int p = 0;
	for (int i = 0; i < l; ++i) {
		if (is[i]) nd[p].cnt++;
		int j = s[i] - 'a';
		if (nd[p].ch[j] == 0) {
			memset(nd + nNd, 0, sizeof(nd[0]));
			nd[p].ch[j] = nNd++;
		}
		p = nd[p].ch[j];
	}
	nd[p].leaf++;
}

void extend_kmp(int ls, char s[], int ext[], int lt, char t[], int next[], bool is[]) {
	int i, j, a, p, k,len;
	next[lt] = 0;
	next[0] = lt;
	j = 0;
	while (1+j < lt && t[j] == t[1+j]) ++j;
	next[1] = j;
	k = 1;
	for (i = 2; i < lt; ++i) {
		p = k + next[k] - 1;
		len = next[i - k];
		if (i + len - 1 < p) next[i] = len;
		else {
			j = p - i + 1;
			if (j < 0) j = 0;
			while (i+j < lt && t[i+j] == t[j]) ++j;
			next[i] = j;
			k = i;
		}
	}
	ext[ls] = 0;
	j = 0;
	while (j < ls && j < lt && s[j] == t[j]) ++j;
	ext[0] = j;
	k = 0;
	for (i = 1; i < ls; ++i) {
		p = k + ext[k] - 1;
		len = next[i - k];
		if (i + len - 1 < p) ext[i] = len;
		else {
			j = p - i + 1;
			if (j < 0) j = 0;
			while (i + j < ls && j < lt && s[i+j] == t[j]) ++j;
			ext[i] = j;
			k = i;
		}
	}
	for (i = 0; i <= ls; ++i) {
		if (ext[i] == ls - i) is[i] = true;
		else is[i] = false;
	}
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		memset(nd, 0, sizeof(nd[0]));
		nNd = 1;
		int x = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d %s", &len[i], s0 + x);
			bg[i] = x;
			for (int j = 0; j < len[i]; ++j) {
				s1[x + j] = s0[x + len[i] - j - 1];
			}
			s1[x + len[i]] = 0;
			extend_kmp(len[i], s0 + x, ext0 + x, len[i], s1 + x, next, is0 + x);
			extend_kmp(len[i], s1 + x, ext1 + x, len[i], s0 + x, next, is1 + x);
			insert(len[i], s0 + x, is0 + x);
			x += len[i] + 1;
		}
		long long ans = 0;
		for (int i = 0; i < n; ++i) {
			int p = 0, j = 0;
			for (j = bg[i]; j < bg[i] + len[i]; ++j) {
				p = nd[p].ch[s1[j] - 'a'];
				if (p == 0) break;
				if (is1[j+1]) ans += nd[p].leaf;
			}
			if (p) ans += nd[p].cnt;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

