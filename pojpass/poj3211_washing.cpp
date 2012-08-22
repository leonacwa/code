#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 101;
const int MM = 11;

int color_cnt;
char color[MM][12];
int get_color_id(const char *s)
{
	for (int i = 0; i < color_cnt; ++i) {
		if (0 == strcmp(color[i], s)) return i;
	}
	strcpy(color[color_cnt], s);
	return color_cnt;
}

struct Cloth {
	int t, c;
};
bool cmpc(const Cloth &a, const Cloth &b) {
	return a.c < b.c;
}
int n, m;
Cloth c[NN];
bool f[100000+100];

int main()
{
	while (EOF != scanf("%d %d", &m, &n) && m > 0 && n > 0) {
		color_cnt = m;
		for (int i = 0; i < color_cnt; ++i) {
			scanf("%s", color[i]);
		}
		for (int i = 0; i < n; ++i) {
			char s[12];
			scanf("%d %s", &c[i].t, s);
			c[i].c = get_color_id(s);
		}
		sort(c, c+n, cmpc);
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			int sum = 0;
			int j;
			for (j = i; j < n; ++j) {
				if (c[j].c != c[i].c) break;
				sum += c[j].t;
			}
			memset(f, 0, sizeof(f));
			f[0] = true;
			for (int k = i; k < j; ++k) {
				for (int v = sum; v >= c[k].t; --v) {
					if (f[v-c[k].t]) {
						f[v] = true;
					}
				}
			}
			int v;
			for (v = sum / 2; v >= 0; --v) {
				if (f[v]) {
					break;
				}
			}
			ans += sum - v;
			i = j - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
