/*
 * CF 252 B. Unsorting Array
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int a[MAXN];

bool is_ok(int n, int a[]) {
	bool w = true, g = true;
	for (int i = 1; i < n; ++i) {
		if (a[i-1] < a[i]) g = false;
		else if (a[i-1] > a[i]) w = false;
		if (!(w || g)) return false;
	}
	return true;
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		bool gw = is_ok(n, a);
		//printf("gw %d\n", gw);
		int x = 0, y = -1;
		for (int i = 1; i < n; ++i) {
			if (a[x] != a[i]) {
				swap(a[x], a[i]);
				if (is_ok(n, a)) {
					swap(a[x], a[i]);
				} else {
					y = i;
					break;
				}
			}
		}
		if (y == -1) {
			int z = 1;
			for (z = 1; z < n; ++z) {
				if (a[z] != a[0]) break;
			}
			if (z < n)
			for (int i = 0; i < n; ++i) {
				if (z != i && a[z] != a[i]) {
					swap(a[z], a[i]);
					if (is_ok(n, a)) {
						swap(a[z], a[i]);
					} else {
						x = i, y = z;
						break;
					}
				}
			}
		}
		if (y != -1) {
			printf("%d %d\n", x+1, y+1);
		} else {
			puts("-1");
		}
	}
	return 0;
}
