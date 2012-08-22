// hlg 1153
#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
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
	int flag, x, y, yx, a, b;
	while (EOF != scanf("%d %d", &x, &y)) {
		flag = 0;
		if (y % x == 0) {
			yx = y / x;
			for (a = (int)sqrt((double)yx); a >= 1; a--) {
				if (yx % a == 0) {
					b = yx / a;
					if (1 == gcd(b, a)) {
						flag = 1;
						break;
					}
				}
			}
		}
		if (flag) 
			printf("%d\n", (a+b)*x);
		else 
			printf("Vagaa\n");
	}
	return 0;
}
