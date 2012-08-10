#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int vx, vl, t1, t2, s;
		scanf("%d %d %d %d %d", &vx, &vl, &t1, &t2, &s);
		double d = t1 * vx;
		int ans = 0;
		if (vx >= vl) {
			printf("0\n");
			continue;
		}
		while (d < s) {
			double t = d / (vl - vx);
			if (d + vx * t >= s) break;
			++ans;
			double _t2 = (d + vx * t) / vl + t2;
			d = d + vx * t + _t2 * vx;
		}
		printf("%d\n", ans);
	}
	return 0;
}

