/* HDU 4281 Judges' response
 * 状态DP：1.普通的状态DP 2.mTSP的状态DP
 * */
#include <cstdio>
#include <cstring>
#include <cmath>

struct Point {
	int x, y;
};
Point pt[17];
int c[17];
int f[1<<17];
int st[1<<17];
int ct[1<<17][17];

int get_dis(Point a, Point b) {
	double x = a.x - b.x, y = a.y - b.y;
	return (int)ceil(sqrt(x*x + y*y));
}

int get_t(int s) {
	int i = 0, ret = 0;
	while (s) {
		if (s&1) ret += c[i];
		++i;
		s >>= 1;
	}
	return ret;
}

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++i) scanf("%d%d", &pt[i].x, &pt[i].y);
		for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
		int all = (1<<n) - 1;
		int n_st = 0;
		memset(f, -1, sizeof(f));
		for (int i = 0; i <= all; ++i) {
			int t = get_t(i);
			if (t <= m) {
				f[i] = 1;
				st[n_st++] = i;
			}
		}
		for (int s = 1; s <= all; ++s) {
			for (int j = 0; j < n_st; ++j) {
				if ((s & st[j]) == 0 && f[s] != -1) {
					int s2 = s | st[j], t = f[s] + f[st[j]];
					if (f[s2] == -1 || f[s2] > t) f[s2] = t;
				}
			}
		}
		int ans1 = f[all];
		if (ans1 == -1) {
			puts("-1 -1");
			continue;
		}
		memset(ct, -1, sizeof(ct));
		for (int i = 1; i < n; ++i) {
			ct[1<<i|1][i] = get_dis(pt[0], pt[i]);
		}
		for (int s = 1; s <= all; ++s) {
			for (int i = 1; i < n; ++i) {
				if ((s & (1<<i)) && ct[s][i] != -1) {
					for (int j = 1; j < n; ++j) {
						if (s & (1<<j)) continue;
						int s2 = s | (1<<j);
						if (get_t(s2) <= m) {
							int t = ct[s][i] + get_dis(pt[i], pt[j]);
							if (ct[s2][j] == -1 || ct[s2][j] > t) {
								ct[s2][j] = t;
							}
						}
					}
				}
			}
		}
		memset(f, -1, sizeof(f));
		for (int s = 1; s <= all; ++s) {
			for (int i = 1; i < n; ++i) {
				if ((s & (1<<i)) && ct[s][i] != -1) {
					ct[s][i] += get_dis(pt[0], pt[i]);
					if (f[s] == -1 || f[s] > ct[s][i]) f[s] = ct[s][i];
				}
			}
		}
		n_st = 0;
		for (int s = 1; s <= all; ++s) {
			if (f[s] != -1)	st[n_st++] = s;
		}
		for (int s = 1; s <= all; ++s) {
			for (int j = 0; j < n_st; ++j) {
				if (0 == ((s&st[j])^1) && f[s] != -1) {
					int s2 = s | st[j], t = f[s] + f[st[j]];
					if (f[s2] == -1 || f[s2] > t) f[s2] = t;
				}
			}
		}
		printf("%d %d\n", ans1, f[all]);
	}
	return 0;
}
