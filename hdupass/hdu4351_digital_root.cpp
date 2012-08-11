/* Digital root
 * 线段树解法：
 * 每个节点记录该点表示的区间是否存在前缀和数字根为k，后缀和数字根为k，子区间和数字根为k的。
 * 维护之~
 *
 * 做题遇到的错误：
 * unsigned short 类型没有负数，但是ushort类型在做减法时出现了负数，导致出错，以后要慎用unsigned数
 * 输入时注意输入范围，尽量使用int类型，如果使用short更短的类型，一定要注意输入和运算过程中的结果范围
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 100005;

short s[MAXN<<2], ls[MAXN<<2], rs[MAXN<<2], v[MAXN<<2];

#define set(x, i) ((x)|=(1<<(i)))
#define test(x, i) ((x)&(1<<(i)))

#define LS  (rt<<1)
#define RS  (rt<<1|1)
/*
inline short set(short &x, int i) {
	    return x |= (short)(1<<i);
}
inline short test(short x, int i) {
	    return x & ((short)(1<<i));
}
*/
void PushUp(int rt) {
	s[rt] = s[LS] | s[RS];
	ls[rt] = ls[LS];
	rs[rt] = rs[RS];
	v[rt] = (v[LS] + v[RS] - 1) % 9 + 1;
	if (test(rs[LS], 0) && test(ls[RS], 0)) {
		set(s[rt], 0);
	}
	for (int i = 1; i <= 9; ++i) {
		if (!test(s[rt], i)) {
			for (int j = 1; j <= 9; ++j) {
				if (test(rs[LS], j) && test(ls[RS], (9 + i - j - 1) % 9 + 1)) {
					set(s[rt], i);
					break;
				}
			}
		}
		if (test(ls[RS], i)) {
			set(ls[rt], (v[LS] + i - 1) % 9 + 1);
		}
		if (test(rs[LS], i)) {
			set(rs[rt], (v[RS] + i - 1) % 9 + 1);
		}
	}
}

void make_tree(int rt, int L, int R) {
	if (L == R) {
		int a;
		scanf("%d", &a);
		v[rt] = (a - 1) % 9 + 1;
		s[rt] = 0;
		set(s[rt], v[rt]);
		ls[rt] = rs[rt] = s[rt];
		return;
	}
	int M = (L + R) >> 1;
	make_tree(LS, L, M);
	make_tree(RS, M+1, R);
	PushUp(rt);
}

short query(int rt, int L, int R, int l, int r, short &val, short &l_s, short &r_s) {
	if (l <= L && R <= r) {
		val = v[rt];
		l_s = ls[rt];
		r_s = rs[rt];
		return s[rt];
	}
	int M = (L + R) >> 1;
	short ret = 0, v1 = 0, v2 = 0, l_s1 = 0, l_s2 = 0, r_s1 = 0, r_s2 = 0;
	if (l <= M) {
		ret |= query(LS, L, M, l, r, v1, l_s1, r_s1);
		l_s = l_s1, r_s = r_s1;
	}
	if (M < r) {
		ret |= query(RS, M+1, R, l, r, v2, l_s2, r_s2);
		l_s = l_s2, r_s = r_s2;
	}
	if (l <= M && M < r) {
		l_s = l_s1, r_s = r_s2;
		if (test(r_s1, 0) && test(l_s2, 0)) {
			set(ret, 0);
		}
		for (int i = 1; i <= 9; ++i) {
			if (!test(ret, i)) {
				for (int j = 1; j <= 9; ++j) {
					if (test(r_s1, j) && test(l_s2, (9 + i - j - 1) % 9 + 1)) {
						set(ret, i);
						break;
					}
				}
			}
			if (test(l_s2, i)) {
				set(l_s, (v1 + i - 1) % 9 + 1);
			}
			if (test(r_s1, i)) {
				set(r_s, (v2 + i - 1) % 9 + 1);
			}
		}
	}
	val = (v1 + v2 - 1) % 9 + 1;
	return ret;
}

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		int n, q;
		scanf("%d", &n);
		while (n <= 0) ;
		make_tree(1, 1, n);
		scanf("%d", &q);
		while (q <= 0) ;
		printf("Case #%d:\n", run);
		while (q--) {
			int l, r, cnt = 0;
			short ss, val, l_s, r_s;
			scanf("%d%d", &l, &r);
			ss= query(1, 1, n, l, r, val, l_s, r_s); 
			for (int i = 9; i >= 0 && cnt < 5; --i) {
				if (!test(ss, i)) continue;
				if (cnt) printf(" ");
				++cnt;
				printf("%d", i);
			}
			while (cnt < 5) {
				if (cnt) printf(" ");
				++cnt;
				printf("-1");
			}
			puts("");
		}
		if (run < runs) puts("");
	}
	return 0;
}
