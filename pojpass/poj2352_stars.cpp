#include <stdio.h>
#include <string.h>

const int MAXN = 15000+5;
const int MAXXY = 32000;

int level[MAXN];
int f[MAXXY*3+3];
int n;

int main()
{
	while (EOF != scanf("%d", &n)) {
		memset(level, 0, sizeof (level));
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; i++) {
			int x, y, s = 0, k = 1, l = 0, r = MAXXY;
			scanf("%d %d", &x, &y);
			while (l < r) {
				int mid = (r - l) / 2 + l;
				if (mid < x) { // right
					l = mid + 1;
					s += f[k];
					k = (k << 1) + 1;
				} else { // left
					r = mid;
					f[k]++;
					k <<= 1;
				}
			}
			s += f[k];
			f[k]++;
			level[s]++;
		}
		for (int i = 0; i < n; i++) {
			printf("%d\n",level[i]);
		}
	}
	return 0;
}

