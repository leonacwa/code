/* A Simple Problem with Integers
 * i = a + xk将i分类成取余k余a这几类
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 50005;

int n;
int A[MAXN];
int c[55][MAXN];
int to[11][11];

int lowbit(int x) {
	return x & -x;
}
void add(int c[], int x, int v) {
	for (; x <= n; x += lowbit(x)) c[x] += v;
}
int sum(int c[], int x) {
	int s = 0;
	for (; x > 0; x -= lowbit(x)) s += c[x];
	return s;
}

int query(int x) {
	int de = 0;
	for (int k = 1; k <= 10; ++k) {
		de += sum(c[ to[k][x%k] ], x);
	}
	return de + A[x];
}

template <class T>
int read_num(T *x) { // 输入外挂
	int ch;
	bool sign = 0;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9') && ch != '-') ;
	if (EOF == ch) return EOF;
	if (ch == '-') {
		sign = 1;
		ch = getchar();
	}
	*x = 0;
	while ('0' <= ch && ch <= '9') {
		*x *= 10;
		*x += ch - '0';
		ch = getchar();
	}
	if (sign) *x = -*x;
	return 1;
}

int main() {
	for (int k = 1, cnt = 0; k <= 10; ++k) {
		for (int i = 0; i < k; ++i) {
			to[k][i] = cnt++;
		}
	}
	while (EOF != scanf("%d", &n)) {
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) read_num(&A[i]); //scanf("%d", &A[i]);
		int q;
		scanf("%d", &q);
		while (q--) {
			int cmd, l, r, k, v;
			scanf("%d", &cmd);
			if (cmd == 1) {
				//scanf("%d%d%d%d", &l, &r, &k, &v);
				read_num(&l);
				read_num(&r);
				read_num(&k);
				read_num(&v);
				int cat = to[k][l%k];
				add(c[cat], l, v);
				add(c[cat], r+1, -v);
			} else {
				//scanf("%d", &l);
				read_num(&l);
				printf("%d\n", query(l));
			}
		}
	}
	return 0;
}
