#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;

struct Ball {
	int x, y, vx, vy;
};
Ball b[128];
int n;

void read(Ball&b) {
	scanf("%d %d %d %d", &b.x, &b.y, &b.vx, &b.vy);
}


double dis(const Ball &a, const Ball &b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x*x + y*y);
}

double f(const Ball &ba, const Ball &bb) {
	int a = ba.x - bb.x;
	int b = ba.vx - bb.vx;
	int c = ba.y - bb.y;
	int d = ba.vy - bb.vy;
	int m = b*b + d*d;
	if (m == 0) {
		return dis(ba, bb);
	}
	else {
		double t = (double)(-(a*b + c*d)) / m;
		if (t < 0)
			return dis(ba, bb);
		double x = a + b*t;
		double y = c + d*t;
		return sqrt(x*x + y*y);
	}
}

int test(Ball a, Ball b) {
	double d = f(a, b);
	if (d < 30+1e-8)
	   return -1;	
	else if (d > 100+1e-8)
		return 0;
	return (int)((100- d)*1000);
}

int main()
{
	while (EOF != scanf("%d", &n)) {
		read(b[0]);
		for (int i = 1; i <= n; ++i) {
			read(b[i]);
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			int ret = test(b[0], b[i]);
			if (ret == -1) {
				ans = -1;
				break;
			}
			else {
				ans += ret;
			}	
		}
		if (ans == -1)
			printf("Dead end\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}
