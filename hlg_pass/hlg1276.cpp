#include <stdio.h>
#include <math.h>

int main()
{
	double d1, d2, d3, L, M, V, T;
	while (EOF != scanf("%lf %lf %lf %lf %lf %lf %lf", &d1, &d2, &d3, &L, &M, &V, &T)) {
		double t = (sqrt((d1+d2)*(d1+d2)+d3*d3) + L) / V;
		if (L > M || t > T) {
			puts("No");
		} else {
			puts("Yes");
		}
	}
	return 0;
}

