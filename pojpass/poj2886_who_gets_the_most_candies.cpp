#include <stdio.h>
#include <string.h>
#include <math.h>

const int MAXN = 500000+5;

int n, k;
char name[MAXN][11];
int card[MAXN];

int cn, c[MAXN];
int lowbit(int x) {
	return x & (-x);
}

void add(int x, int v) {
	for (; x <= cn; x += lowbit(x)) {
		c[x] += v;
	}
}

int sum(int x) {
	int s = 0;
	for (; x > 0; x -= lowbit(x)) {
		s += c[x];
	}
	return s;
}

int b_s(int v)
{
	int l = 1, r = n, m;
	while (l < r) {
		m = (r-l)/2 + l;
		if (sum(m) < v) {
			l = m+1;
		} else {
			r = m;
		}
	}
	return l;
}

const int pm[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int max_num, best_num, max_fp;

void anti_prime(int num, int a, int b, int limit)
{
	if (b > max_fp) {
		best_num = num;
		max_fp = b;
	} else if (b == max_fp && num < best_num) {
		best_num = num;
	}
	if (a >= 8) {
		return;
	}
	int tmp = num;
	for (int i = 1; i <= limit; i++) {
		tmp *= pm[a];
		if (tmp <= max_num) {
			anti_prime(tmp, a+1, b*(i+1), i);
		} else {
			break;
		}
	}
}

int main()
{
	while (EOF != scanf("%d %d", &n, &k)) {
		max_num = n;
		best_num = 0;
		max_fp = 0;
		anti_prime(1, 0, 1, (int)(1.0+pow(n*1.0, 0.5)));
		memset(c, 0,  sizeof(c));
		cn = n;
		for (int i = 1; i <= n; i++) {
			scanf("%s %d", name[i], &card[i]);
			add(i, 1);
		}
		int now = k;
		int tn = n;
		int cnt = 0;
		while (tn > 1) {
			add(now, -1);
			cnt++;
			if (cnt == best_num) {
				break;
			}
			int nk;
			if (card[now] > 0) {
				nk = ((k-1+card[now]) % (tn-1) + tn-1-1) % (tn-1) + 1;
			} else {
				nk = ((k+card[now]) % (tn-1) + tn-1-1) % (tn-1) + 1;
			}
			int pos = b_s(nk);
			k = nk;
			now = pos;
			tn--;
		}
		printf("%s %d\n", name[now], max_fp);
	}
	return 0;
}

