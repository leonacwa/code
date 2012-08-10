#include <stdio.h>
#include <string.h>
const int NN = 101;
int ma[NN][NN];
int n;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while(nTest--) {
		scanf("%d", &n);
		memset(ma, 0, sizeof(ma));
		int x = 0, y = 0, id = 1;
		int dx = 0, dy = 1, t;
		while (1) {
			while (0 <= x && x < n && 0 <= y && y < n && ma[x][y] == 0) {
				ma[x][y] = id++;
				x += dx;
				y += dy;
			}
			x -= dx, y -= dy;
			t = dx, dx = dy, dy = t;

			x += dx, y += dy;
			while (0 <= x && x < n && 0 <= y && y < n && ma[x][y] == 0) {
				ma[x][y] = id++;
				x += dx;
				y += dy;
			}
			x -= dx, y -= dy;
			t = dx, dx = dy, dy = t;

			if (dx == 0) dy = -dy;
			else dx = -dx;

			x += dx, y += dy;
			if (0 <= x && x < n && 0 <= y && y < n && ma[x][y] == 0) {
				ma[x][y] = id++;
			} else {
				break;
			}
			t = dx, dx = dy, dy = t;
			x += dx, y += dy;
		}
		for (x = 0; x < n; ++x) {
			for (y = 0; y < n - 1; ++y) {
				printf("%d ", ma[x][y]);
			}
			printf("%d\n", ma[x][y]);
		}
	}
	return 0;
}
