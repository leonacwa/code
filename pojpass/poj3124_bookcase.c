/* The Bookcase
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int INF = 0x3f3f3f3f;

int f[2151][2151];

typedef struct _Book {
	int h, t;
} Book;
Book b[105];

int cmph(const void*a, const void *b) {
	return ((Book*)b)->h - ((Book*)a)->h;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int runs, n;
	int tsum, tmax, i, j, k, ans, h, t, v;
	scanf("%d", &runs);
	while (runs--) {
		scanf("%d", &n);
		tsum = tmax = 0;
		for (i = 0; i < n; ++i) {
			scanf("%d%d", &b[i].h, &b[i].t);
			tsum += b[i].t;
		}
		qsort(b, n, sizeof(b[0]), cmph);
		for (i = 0; i <= tsum - b[0].t; ++i) {
			memset(f[i], 0x3f, sizeof(f[i][0]) * (tsum));
		}
		f[0][0] = 0;
		for (i = 1; i < n; ++i) {
			h = b[i].h, t = b[i].t, v;
			for (j = tmax; j >= 0; --j) {
				for (k = tmax; k >= 0; --k) {
					if (f[j][k] >= INF) continue;
					if (j >  0) {
						if (f[j+t][k] > f[j][k]) f[j+t][k] = f[j][k];
					} else {
						if (f[t][k] > f[0][k]+h) f[t][k] = f[0][k] + h;
					}
					if (k >  0) {
					   if (f[j][k+t] > f[j][k]) f[j][k+t] = f[j][k];
					} else {
						if (f[j][t] > f[j][0]+h) f[j][t] = f[j][0] + h;
					}
				}
			}
			tmax += t;
		}
		ans = INF;
		for (j = 1; j <= tmax; ++j) {
			for (k = tmax - j; k >= 1; --k) {
				if (f[j][k] >= INF) continue;
				t = (f[j][k] + b[0].h) * max(tsum - j - k, max(j, k));
				if (ans > t) ans = t;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
