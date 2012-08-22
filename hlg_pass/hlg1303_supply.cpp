#include <cstdio>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 10;

double asx[NN], asy[NN], avx[NN], avy[NN];
double hx, hy, hs;
int n;
double ans;

double minTime(double sx, double sy, double vx, double vy, double hx, double hy, double hs)
{
	double dx = sx - hx, dy = sy - hy;
	double a = vx*vx + vy*vy - hs*hs;
	double b = 2 * (dx*vx + dy*vy);
	double c = dx*dx + dy*dy;
	double dt = sqrt(b*b - 4*a*c);
	double r1 = (-b + dt) / (2*a);
	double r2 = (-b - dt) / (2*a);
	return min(r1 < 0 ? DBL_MAX : r1, r2 < 0 ? DBL_MAX : r2);
}

double solve(int ar[])
{
	double t = 0, sx, sy, rx = hx, ry = hy;
	for (int i = 0; i < n; ++i) {
		int p = ar[i];
		sx = asx[p] + avx[p] * t;
		sy = asy[p] + avy[p] * t;
		t += minTime(sx, sy, avx[p], avy[p], rx, ry, hs);
		t += 3600;
		rx = asx[p] + avx[p] * t;
		ry = asy[p] + avy[p] * t;
		if (t > ans) return ans;
	}
	sx = rx - hx;
	sy = ry - hy;
	t += sqrt(sx*sx + sy*sy) / hs;
	return t;
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		for (int i = 0; i < n; ++i) {
			scanf("%lf %lf %lf %lf", &asx[i], &asy[i], &avx[i], &avy[i]);
			avx[i] /= 3600;
			avy[i] /= 3600;
		}
		scanf("%lf %lf %lf", &hx, &hy, &hs);
		hs /= 3600;
		int ar[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		ans = DBL_MAX;
		do {
			double t = solve(ar);
			if (ans > t) ans = t;
		} while(next_permutation(ar, ar+n));

		int sec = (int)ceil(ans);
		int h = sec / 3600;
		int m = sec % 3600 / 60;
		int s = sec % 60;
		printf("Case %d: %d hour(s) %d minute(s) %d second(s)\n", ++nCase, h, m, s);
	}
	return 0;
}

