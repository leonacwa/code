/* 黑龙江2012ACM-ICPC省赛
 * F题 AC
 * 以后写熟了就能快速过这种题
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

struct Node {
	int llis, llds, rlis, rlds, mlis, mlds, lv, rv;
	bool f;
} T[MAXN<<2];

char S[MAXN];

void flip(Node &RT) {
	swap(RT.llis, RT.llds);
	swap(RT.rlis, RT.rlds);
	swap(RT.mlis, RT.mlds);
	RT.lv = 9 - RT.lv;
	RT.rv = 9 - RT.rv;
}

void PushUp(int rt, int L, int R) {
	if (L >= R) return;
	Node &RT = T[rt], &LS = T[rt<<1], &RS = T[rt<<1|1];
	int M = (L + R) >> 1;
	RT.llis = LS.llis + (LS.llis == M-L+1 && LS.rv <= RS.lv ? RS.llis : 0);
	RT.llds = LS.llds + (LS.llds == M-L+1 && LS.rv >= RS.lv ? RS.llds : 0);
	RT.rlis = RS.rlis + (RS.rlis == R - M && LS.rv <= RS.lv ? LS.rlis : 0);
	RT.rlds = RS.rlds + (RS.rlds == R - M && LS.rv >= RS.lv ? LS.rlds : 0);
	RT.mlis = max(max(LS.mlis, RS.mlis), LS.rv <= RS.lv ? LS.rlis + RS.llis : 0);
	RT.mlds = max(max(LS.mlds, RS.mlds), LS.rv >= RS.lv ? LS.rlds + RS.llds : 0);
	RT.lv = LS.lv;
	RT.rv = RS.rv;
}

void PushDown(int rt, int L, int R) {
	Node &RT = T[rt], &LS = T[rt<<1], &RS = T[rt<<1|1];
	LS.f ^= RT.f;
	RS.f ^= RT.f;
	if (RT.f) {
		flip(LS);
		flip(RS);
	}
	RT.f = false;
}

void make_tree(int rt, int L, int R) {
	Node &RT = T[rt];
	RT.f = false;
	if (L == R) {
		RT.lv = RT.rv = S[L] - '0';
		RT.llis = RT.llds = RT.rlis = RT.rlds = RT.mlis = RT.mlds = 1;
	} else {
		int M = (L + R) >> 1;
		make_tree(rt<<1, L, M);
		make_tree(rt<<1|1, M+1, R);
		PushUp(rt, L, R);
	}
}

void update(int rt, int L, int R, int l, int r, bool f) {
	Node &RT = T[rt];
	if (l <= L && R <= r) {
		if (f) {
			flip(RT);
			RT.f ^= true;
		}
		return;
	}
	if (L >= R) return;
	PushDown(rt, L, R);
	int M = (L + R) >> 1;
	if (l <= M) update(rt<<1, L, M, l, r, f);
	if (M < r) update(rt<<1|1, M+1, R, l, r, f);
	PushUp(rt, L, R);
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n, m;
		scanf("%d%d%s", &n, &m, S+1);
		make_tree(1, 1, n);
		while (m--) {
			char cmd[32];
			int a, b;
			scanf("%s", cmd);
			if (cmd[0] == 'q') {
				printf("%d\n", T[1].mlis);
			} else {
				scanf("%d%d", &a, &b);
				update(1, 1, n, a, b, true);
			}
		}
		puts("");
	}
	return 0;
}

