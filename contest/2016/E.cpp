#include <stdio.h>
#include <math.h>

const double PI = 3.14159267;
const double eps = 1e-6;

int main()
{
	int n, R, r;
	while (EOF != scanf("%d %d %d", &n, &R, &r)) {
		double a = PI / n;
		if (n == 1) {
			if (R >= r) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
			continue;
		}
		double rt = r / (sin(a));
		if (R - r >= rt - eps) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
		//printf("%f %f\n", a, rt);
	}
	return 0;
}

