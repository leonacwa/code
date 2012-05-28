// 树状数组解法
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 50000 + 100;
int n, m, C[MAXN];

int lowbit(int x) {
	return x & -x;
}

void add(int x, int val)
{
	for (; x <= n; x += lowbit(x)) {
		C[x] += val;
	}
}

int sum(int x)
{
	int ret = 0;
	for (; x > 0; x -= lowbit(x)) {
		ret += C[x];
	}
	return ret;
}

int bin(int val)
{
	if (val == 0) {
		return 0;
	}
	if (sum(n) == val - 1) {
		return n + 1;
	}
	int l = 1, r = n;
	while (l < r) {
		int m = (r - l) / 2 + l;
		if (sum(m) < val) {
			l = m + 1;
		} else {
			r = m;
		}
	}
	return l;
}

bool des[MAXN];
int st[MAXN];

int main()
{
	while (EOF != scanf("%d %d", &n, &m)) {
		memset(C, 0, sizeof(C));
		memset(des, 0, sizeof(des));
		int top = 0;
		while (m--) {
			char cmd[32];
			int x;
			scanf("%s", cmd);
			if ('D' == cmd[0]) {
				scanf("%d", &x);
				if (des[x] == false) {
					des[x] = true;
					add(x, 1);
				}
				st[top++] = x;
			} else if ('R' == cmd[0]) {
				x = st[--top];
				if (des[x] == true) {
					des[x] = false;
					add(x, -1);
				}
			} else if ('Q' == cmd[0]) {
				scanf("%d", &x);
				if (des[x]) {
					puts("0");
				} else {
					x = sum(x);
					int p1 = bin(x);
					int p2 = bin(x + 1);
					printf("%d\n", p2 - p1 - 1);
				}
			}
		}
	}
	return 0;
}

