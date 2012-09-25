/* A. Where do I Turn?
 * */

#include <cstdio>
#include <cstring>

typedef long long int64;

int64 cross(int64 x1, int64 y1, int64 x2, int64 y2) {
	return x1 * y2 - y1 * x2;
}

int main() {
	int x[3], y[3];
	while (EOF != scanf("%d%d%d%d%d%d", x+0, y+0, x+1, y+1, x+2, y+2)) {
		int64 r = cross(x[2] - x[0], y[2] - y[0], x[1] - x[0], y[1] - y[0]);
		if (r < 0) {
			puts("LEFT");
		} else if (r > 0) {
			puts("RIGHT");
		} else {
			puts("TOWARDS");
		}
	}
	return 0;
}
