#include <stdio.h>

const int MAXN = 455+5;

struct Point {
	int x, y;
};
Point pt[MAXN];
int ans[MAXN*MAXN*MAXN/3][3];

bool in_line(int i, int j, int k)
{
	return (pt[i].y - pt[j].y) * (pt[j].x - pt[k].x) == (pt[j].y - pt[k].y) * (pt[i].x - pt[j].x);
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
		}
		int x = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				for(int k = j+1; k < n; k++) {
					if (in_line(i, j, k)) {
						ans[x][0] = i + 1;
						ans[x][1] = j + 1;
						ans[x][2] = k + 1;
						x++;
					}
				}
			}
		}
		printf("%d\n", x);
		for (int i = 0; i < x; i++) {
			printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
		}
	}
	return 0;
}

