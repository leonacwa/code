#include <cstdio>
#include <cstring>
#include <cassert>

const int MAXN = (int)1e6 + 5;

int nd_cnt;
int root, ncnt[MAXN];
int nd[MAXN][26];

int new_node() {
	assert( nd_cnt < MAXN );
	memset(nd[nd_cnt], -1, sizeof(int) * 26);
	ncnt[nd_cnt] = 0;
	return nd_cnt++;
}

void insert(char *s, int v) {
	int p = 0;
	for (; *s; s++) {
		assert('a' <= *s && *s <= 'z');
		int c = *s - 'a';
		if (nd[p][c] == -1) {
			nd[p][c] = new_node();
		}
		ncnt[p] += v;
		p = nd[p][c];
	}
	ncnt[p] += v;
}

int find(char *s) {
	int p = 0;
	for (; *s; s++) {
		assert('a' <= *s && *s <= 'z');
		int c = *s - 'a';
		if (nd[p][c] == -1) return 0;
		p = nd[p][c];
	}
	return ncnt[p];
}

int main() {
	int T, n, m;
	char str[100];
	nd_cnt = 0;
	root = new_node();
	while (gets(str)) {
		if (str[0] == '\0') break;
		insert(str, 1);
	}
	while (gets(str)) {
		printf("%d\n", find(str));
	}
	return 0;
}
