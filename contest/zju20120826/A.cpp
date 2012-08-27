/* Alice's present
 * RMQ问题的应用
 * */
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 500005;

#define LS (rt<<1)
#define RS (rt<<1|1)

int left_pos[MAXN], val[MAXN];
int maxR[MAXN << 2];

void make_tree(int rt, int L, int R) {
	if (L == R) {
		maxR[rt] = left_pos[L];
		return;
	}
	int M = (L + R) >> 1;
	make_tree(LS, L, M);
	make_tree(RS, M+1, R);
	maxR[rt] = max(maxR[LS], maxR[RS]);
}

int query(int rt, int L, int R, int l, int r) {
	if (l <= L && R <= r) {
		return maxR[rt];
	}
	if (L == R) return 0;
	int M = (L + R) >> 1;
	int p = 0;
	if (M < r) p = query(RS, M+1, R, l, r);
	if (p != 0 && l <= p) {
		int pl = 0;
		if (l <= M) pl = query(LS, L, M, l, r);
		if (l <= pl && pl > p) return pl;
		return p;
	}
	if (l <= M) p = query(LS, L, M, l, r);
	if (l <= p) return p;
	return 0;
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		map<int, int> ma;
		for (int i = 1, t; i <= n; ++i) {
			scanf("%d", &t);
			val[i] = t;
			left_pos[i] = ma[t];
			ma[t] = i;
		}
		make_tree(1, 1, n);
		int q;
		scanf("%d", &q);
		while (q--) {
			int a, b;
			scanf("%d%d", &a, &b);
			int p = query(1, 1, n, a, b);
			if (p == 0) {
				puts("OK");
			} else {
				printf("%d\n", val[p]);
			}
		}
		puts("");
	}
	return 0;
}
