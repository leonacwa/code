#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

const int NN = 100;

const double eps = 0;//1e-12;
struct Ball {
	double x, y, z, r;
};
bool inB(const Ball &b, double ox, double oy, double oz) {
	double xt = b.x - ox, yt = b.y - oy, zt = b.z - oz;
	return xt * xt + yt * yt + zt * zt - eps <= b.r * b.r;
}

struct Ellipse {
	double x, y, z, a, b, c;
};

bool inE(const Ellipse &e, double ox, double oy, double oz) {
	double xt = e.x - ox, yt = e.y - oy, zt = e.z - oz;
	return xt * xt / e.a / e.a + yt * yt / e.b / e.b + zt * zt / e.c / e.c - eps <= 1.0;
}
struct Paralle {
	double x1, y1, z1, x2, y2, z2;
};

bool inP(const Paralle &p, double ox, double oy, double oz) {
	return ((p.x1 - eps <= ox && ox <= p.x2 + eps) || (p.x2 - eps <= ox && ox <= p.x1 + eps)) &&
		((p.y1 - eps <= oy && oy <= p.y2 + eps) || (p.y2 - eps <= oy && oy <= p.y1 + eps)) &&
		((p.z1 - eps <= oz && oz <= p.z2 + eps) || (p.z2 - eps <= oz && oz <= p.z1 + eps));
}
struct Cube {
	double x, y, z, d;
};

bool inC(const Cube &c, double ox, double oy, double oz) {
	double xt = 2*abs(c.x - ox), yt = 2*abs(c.y - oy), zt = 2*abs(c.z - oz);
	return xt - eps <= c.d && yt - eps <= c.d && zt - eps <= c.d;
}

int nB, nE, nP, nC;
Ball b[NN], newB;
Ellipse e[NN], newE;
Paralle p[NN], newP;
Cube c[NN], newC;

bool in(double x, double y, double z)
{
	for (int i = 0; i < nB; ++i) if (inB(b[i], x, y, z)) return true;
	for (int i = 0; i < nE; ++i) if (inE(e[i], x, y, z)) return true;
	for (int i = 0; i < nP; ++i) if (inP(p[i], x, y, z)) return true;
	for (int i = 0; i < nC; ++i) if (inC(c[i], x, y, z)) return true;
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
					bool is = false;
					if (type[0] == 'b') is = inB(newB, x, y, z);
					else if (type[0] == 'e') is = inE(newE, x, y, z);
					else if (type[0] == 'p') is = inP(newP, x, y, z);
					else if (type[0] == 'c') is = inC(newC, x, y, z);
					if (is && !in(x, y, z)) {
						ans += 0.01 * 0.01 * 0.01;
					}
				}
			}
		}
		printf("Scenario #%d\n%.2f\n\n", ++nCase, ans);
	}
	return 0;
}
