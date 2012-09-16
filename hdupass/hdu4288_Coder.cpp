/* HDU 4288 Coder
 * 线段树
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 100005;

struct OP {
	char c;
	int x;
} op[MAXN];

struct Node {
	int sz;
	int64 s[5];
} T[MAXN<<2];

int tot, a[MAXN];
bool sf[MAXN];

int find(int x) {
	int l = 1, r = tot, m;
	while (l <= r) {
		m = (l + r) >> 1;
		if (a[m] == x) return m;
		if (a[m] < x) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

#define LS (rt<<1)
#define RS (rt<<1|1)

void PushUp(int rt, int L, int R) {
	if (L >= R) return;
	T[rt].sz = T[LS].sz + T[RS].sz;
	int lsz = T[LS].sz;
	for (int i = 0; i < 5; ++i) {
		int j = (lsz + i) % 5;
		T[rt].s[j] = T[LS].s[j] + T[RS].s[i];
	}
}

void makeTree(int rt, int L, int R) {
	memset(&T[rt], 0, sizeof(T[rt]));
	if (L == R) {
		sf[L] = false;
		return;
	}
	int M = (L + R) >> 1;
	makeTree(LS, L, M);
	makeTree(RS, M+1, R);
}

void update(int rt, int L, int R, int x, bool f) {
	if (L == R) {
		if (L == x) {
			sf[x] = f;
			T[rt].sz = f ? 1 : 0;
			T[rt].s[1] = f ? a[x] : 0;
		}
		return;
	}
	int M = (L + R) >> 1;
	if (x <= M) update(LS, L, M, x, f);
	else update(RS, M+1, R, x, f);
	PushUp(rt, L, R);
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		tot = 0;
		for (int i = 0; i < n; ++i) {
			char cmd[15];
			scanf("%s", cmd);
			op[i].c = cmd[0];
			if (cmd[0] != 's') {
				scanf("%d", &op[i].x);
				a[++tot] = op[i].x;
			}
		}
		sort(a+1, a+tot+1);
		int *end = unique(a+1, a+tot+1);
		tot = end - a - 1;
		makeTree(1, 1, tot);
		for (int i = 0; i < n; ++i) {
			if (op[i].c == 's') {
				printf("%lld\n", T[1].s[3]);
			} else {
				int p = find(op[i].x);
				while (p < 0) ;
				update(1, 1, tot, p, op[i].c == 'a');
			}
		}
	}
	return 0;
}
