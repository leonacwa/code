// http://acm.hrbeu.edu.cn/index.php?act=problem&id=1004&cid=70
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

char sa[100], sb[100], so1[100], so2[100], so3[100];

int gcd(int a, int b)
{
	int t;
	while (b) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int main()
{
	int nCase = 0, a, b, sign;
	char *pc;
	while (EOF != scanf(" %s %s %d %s %s", sa, so1, &b, so2, so3)) {
		if (isdigit(sa[0]) || ((sa[0] == '-') && isdigit(sa[1]))) {
			pc = sa;
			if (*pc == '-') {
				sign = -1;
				++pc;
			} else {
				sign = 1;
			}
			a = 0;
			while (*pc && *pc != 'x') {
				a = a * 10 + *pc - '0';
				++pc;
			}
			a *= sign;
		} else if (sa[0] == 'x') {
			a = 1;
		} else {
			a = -1;
		}

		sign = 1;
		if (so1[0] == '-') {
			sign = -1;
		}
		b = -1 * sign * b;

		if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
			sign = -1;
		} else {
			sign = 1;
		}
		a = abs(a);
		b = abs(b);

		printf("Case %d:\n", ++nCase);
		if (b == 0) {
			printf("0\n");
		} else {
			int g = gcd(b, a);
			if (g == a) {
				printf("%d\n", sign * b / a);
			} else {
				printf("%s%d/%d\n", sign >= 0 ? "" : "-", b / g, a / g);
			}
		}
	}
	return 0;
}

