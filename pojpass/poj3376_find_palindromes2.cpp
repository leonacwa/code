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
	next[0] = lt;
	k = 1;
	j = -1;
	for (i = 1; i < lt; ++i, --j) {
		if (j < 0 || i + next[i - k] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < lt && t[p] == t[j]) ++j, ++p;
			next[i] = j, k = i;
		}
		else next[i] = next[i - k];
	}
	j = -1;
	for (i = 0; i < ls; ++i, --j) {
		if (j < 0 || i + next[i - k] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < ls && j < lt && s[p] == t[j]) ++j, ++p;
			ext[i] = j, k = i;
		}
		else ext[i] = next[i - k];
	}
	ext[ls] = 0;
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

