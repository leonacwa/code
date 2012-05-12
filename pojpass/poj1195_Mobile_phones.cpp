#include <stdio.h>
#include <string.h>

const int MAXS = 1024+1;
int c[MAXS][MAXS];
int S;

inline int lowbit(int x)
{
	return x & (-x);
}

void add(int x, int y, int v)
{
	for (int i = x; i <= S; i += lowbit(i)) {
		for (int j = y; j <= S; j += lowbit(j)) {
			c[i][j] += v;
		}
	}
}

int sum(int x, int y)
{
	int s = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		for (int j = y; j > 0; j -= lowbit(j)) {
			s += c[i][j];
		}
	}
	return s;
}
int sum2(int x1, int y1, int x2, int y2)
{
	return sum(x2, y2) + sum(x1-1, y1-1) - sum(x1-1, y2) - sum(x2, y1-1);
}

int main()
{
	int ins;
	while (EOF != scanf("%d", &ins)) {
		if (ins == 0) {
			scanf("%d", &S);
			memset(c, 0, sizeof(c));
		} else if (ins == 1) {
			int x, y, a;
			scanf("%d %d %d", &x, &y, &a);
			add(x+1, y+1, a);
		} else if (ins == 2) {
			int l, b, r, t;
			scanf("%d %d %d %d", &l, &b, &r, &t);
			printf("%d\n", sum2(l+1, b+1, r+1, t+1));
		} else {
		}
	}
	return 0;
}

