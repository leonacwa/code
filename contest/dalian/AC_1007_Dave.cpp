#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
int n, r;
struct NODE {
	int x, y;
} nlist[1005], tlist[1005];
bool cmpx(const NODE &a, const NODE &b) {
	if (a.x == b.x) {
		return a.y < b.y;
	} else {
		return a.x < b.x;
	}
}
bool cmpy(const NODE &a, const NODE &b) {
	if (a.y == b.y) {
		return a.x < b.x;
	} else {
		return a.y < b.y;
	}
}
int main() {
	int left, right, i, cnt, ti, tj, ans, tans;
	while (scanf("%d%d", &n, &r) != EOF) {
		for (i = 0; i < n; i++) {
			scanf("%d%d", &nlist[i].x, &nlist[i].y);
		}
		sort(nlist, nlist + n, cmpx);
		right = 0;
		ans = 0;
		for (left = 0; left < n; left++) {
			for (; right < n; right++) {
				if (nlist[right].x - nlist[left].x <= r) {
					
				} else {
					right--;
					break;
				}
			}
			if (right >= n) right = n - 1;
			cnt = 0;
			//printf("%d %d\n", left, right);
			for (i = left; i <= right; i++) {
				tlist[cnt++] = nlist[i];
			}
			sort(tlist, tlist + cnt, cmpy);
			tj = 0;
			for (ti = 0; ti < cnt; ti++) {
				for (; tj < cnt; tj++) {
					if (tlist[tj].y - tlist[ti].y <= r) {
						
					} else {
						tj--;
						break;
					}
				}
				if (tj >= cnt) tj = cnt - 1;
				ans = max(ans, tj - ti + 1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
