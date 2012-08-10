#include <stdio.h>

int abs(int a) {
	return a >= 0 ? a: -a;
}

int gcd(int a, int b) {
	while (b) {
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int main()
{
	int a, b, c, d;
	char op;
	while (EOF != scanf("%d/%d%c%d/%d", &a, &b, &op, &c, &d)) {
		int bb = b * d;
		int aa;
		if (op == '-') {
			aa = a * d - c * b;
		} else {
			aa = a * d + c * b;
		}
		int sign = aa * bb;
		if (aa == 0) {
			printf("0\n");
		} else {
			aa = abs(aa);
			bb = abs(bb);
			int g =gcd(aa, bb);
			aa /= g;
			bb /= g;
			if (bb > 1) {
				printf("%s%d/%d\n", sign<0?"-":"", aa, bb);
			} else {
				printf("%s%d\n", sign<0?"-":"", aa);
			}
		}
	}
	return 0;
}

