#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

const int NN = 100;

const double eps = 0;//1e-12;
struct Ball {
	double x, y, z, r;
	bool in(double ox, double oy, double oz) {
		double xt = x - ox, yt = y - oy, zt = z - oz;
		return xt * xt + yt * yt + zt * zt - eps <= r * r;
	}
};

struct Ellipse {
	double x, y, z, a, b, c;
	bool in(double ox, double oy, double oz) {
		double xt = x - ox, yt = y - oy, zt = z - oz;
		return xt * xt / a / a+ yt * yt / b / b + zt * zt / c / c - eps <= 1.0;
	}
};
struct Paralle {
	double x1, y1, z1, x2, y2, z2;
	bool in(double ox, double oy, double oz) {
		return ((x1 - eps <= ox && ox <= x2 + eps) || (x2 - eps <= ox && ox <= x1 + eps)) &&
			((y1 - eps <= oy && oy <= y2 + eps) || (y2 - eps <= oy && oy <= y1 + eps)) &&
			((z1 - eps <= oz && oz <= z2 + eps) || (z2 - eps <= oz && oz <= z1 + eps));
	}
};
struct Cube {
	double x, y, z, d;
	bool in(double ox, double oy, double oz) {
		double xt = 2*abs(x - ox), yt = 2*abs(y - oy), zt = 2*abs(z - oz);
		return xt - eps <= d && yt - eps <= d && zt - eps <= d;
	}
};
int nB, nE, nP, nC;
Ball b[NN], newB;
Ellipse e[NN], newE;
Paralle p[NN], newP;
Cube c[NN], newC;

bool in(double x, double y, double z)
{
	for (int i = 0; i < nB; ++i) if (b[i].in(x, y, z)) return true;
	for (int i = 0; i < nE; ++i) if (e[i].in(x, y, z)) return true;
	for (int i = 0; i < nP; ++i) if (p[i].in(x, y, z)) return true;
	for (int i = 0; i < nC; ++i) if (c[i].in(x, y, z)) return true;
	return false;
}

int main()
{
	int nCase = 0;
	char type[32];
	int id, n;
	while (EOF != scanf("%d", &n)) {
		nB = nE = nP = nC = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%*s %s", type);
			if ('b' == type[0]) {
				scanf("%lf %lf %lf %lf", &b[nB].x, &b[nB].y, &b[nB].z, &b[nB].r);
				++nB;
			} else if ('e' == type[0]) {
				scanf("%lf %lf %lf %lf %lf %lf", &e[nE].x, &e[nE].y, &e[nE].z, &e[nE].a, &e[nE].b, &e[nE].c);
				++nE;
			} else if ('p' == type[0]) {
				scanf("%lf %lf %lf %lf %lf %lf", &p[nP].x1, &p[nP].y1, &p[nP].z1, &p[nP].x2, &p[nP].y2, &p[nP].z2);
				++nP;
			} else if ('c' == type[0]) {
				scanf("%lf %lf %lf %lf", &c[nC].x, &c[nC].y, &c[nC].z, &c[nC].d);
				++nC;
			} else puts("error");
		}
		scanf("%*s %s", type);
		if ('b' == type[0]) {
			scanf("%lf %lf %lf %lf", &newB.x, &newB.y, &newB.z, &newB.r);
		} else if ('e' == type[0]) {
			scanf("%lf %lf %lf %lf %lf %lf", &newE.x, &newE.y, &newE.z, &newE.a, &newE.b, &newE.c);
		} else if ('p' == type[0]) {
			scanf("%lf %lf %lf %lf %lf %lf", &newP.x1, &newP.y1, &newP.z1, &newP.x2, &newP.y2, &newP.z2);
		} else if ('c' == type[0]) {
			scanf("%lf %lf %lf %lf", &newC.x, &newC.y, &newC.z, &newC.d);
		}
		double ans = 0.0;
		for (double x = -0.5; x <= 0.5; x += 0.01) {
			for (double y = -0.5; y <= 0.5; y += 0.01) {
				for (double z = -0.5; z <= 0.5; z += 0.01) {
					if (!in(x, y, z)) {
						bool is = false;
						if (type[0] == 'b') is = newB.in(x, y, z);
						else if (type[0] == 'e') is = newE.in(x, y, z);
						else if (type[0] == 'p') is = newP.in(x, y, z);
						else if (type[0] == 'c') is = newC.in(x, y, z);
						if (is) {
							ans += 0.01 * 0.01 * 0.01;
						}
					}
				}
			}
		}
		printf("Scenario #%d\n%.2f\n\n", ++nCase, ans);
	}
	return 0;
}

