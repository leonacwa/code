/* Tower Parking
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 2505;

struct Car {
	int f, p;
} c[MAXN];

int dy[MAXN];

int abs(int a) {
	return a < 0 ? -a : a;
}
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int h, l, tot = 0;
		scanf("%d%d", &h, &l);
		for (int i = 0; i < h; ++i) {
			dy[i] = 0;
			for (int j = 0, r; j < l; ++j) {
				scanf("%d", &r);
				if(r != -1) {
					c[r].f = i, c[r].p = j;
					++tot;
				}
			}
		}
		int ans = 0;
		for (int i = 1; i <= tot; ++i) {
			ans += c[i].f * 10 * 2;
			int y = ((c[i].p + dy[c[i].f]) % l + l) % l;
			if (y <= l - y) {
				ans += y * 5;
				dy[c[i].f] -= y;
			} else {
				ans += (l - y) * 5;
				dy[c[i].f] += (l - y);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
