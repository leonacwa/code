/* Query
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 1000005;

char s[2][MAXN];
int l[2];
int len[MAXN<<2];

void PushUp(int rt, int L, int R) {
	int M = (L + R) >> 1, LS = rt<<1, RS = rt<<1|1;
	if (len[LS] == M - L + 1) len[rt] = len[LS] + len[RS];
	else len[rt] = len[LS];
}

void make_tree(int rt, int L, int R) {
	if (L == R) {
		len[rt] = (L < l[0] && L < l[1] && s[0][L] == s[1][L]);
		return;
	}
	int M = (L + R) >> 1;
	make_tree(rt<<1, L, M);
	make_tree(rt<<1|1, M+1, R);
	PushUp(rt, L, R);
}

void update(int rt, int L, int R, int a, int i, char c) {
	if (L == R && L == i) {
		s[a][i] = c;
		len[rt] = (L < l[0] && L < l[1] && s[0][L] == s[1][L]);
		return;
	}
	int M = (L + R) >> 1;
	if (i <= M) update(rt<<1, L, M, a, i, c);
	else update(rt<<1|1, M+1, R, a, i, c);
	PushUp(rt, L, R);
}

int query(int rt, int L, int R, int i) {
	if (L == i) {
		return len[rt];
	}
	int M = (L + R) >> 1, ret;
	if (i <= M) {
		ret = query(rt<<1, L, M, i);
		if (ret == M - i + 1) {
			ret += query(rt<<1|1, M+1, R, M+1);
		}
	} else {
		ret = query(rt<<1|1, M+1, R, i);
	}
	return ret;
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		scanf("%s%s", s[0], s[1]);
		l[0] = strlen(s[0]);
		l[1] = strlen(s[1]);
		int n = l[0];
		if (n > l[1]) n = l[1];
		make_tree(1, 0, n-1);
		printf("Case %d:\n", run);
		int q, cmd, a, i; char c[32];
		scanf("%d", &q);
		while (q--) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d%d%s", &a, &i, c);
				if (i < l[0] && i < l[1]) {
					--a;
					update(1, 0, n-1, a, i, *c);
				}
			} else {
				scanf("%d", &i);
				if (i < l[0] && i < l[1]) {
					printf("%d\n", query(1, 0, n-1, i));
				} else {
					puts("0");
				}
			}
		}
	}
	return 0;
}
