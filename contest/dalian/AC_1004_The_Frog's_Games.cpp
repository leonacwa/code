#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
int l, n, m;
int dis[500005];
int test(int mid) {
	int i, np = 0, tim = 0, nl = 0;
	int ni = 0;
	for (i = 1; i < n && tim <= m; i++) {
		if (dis[i] - dis[ni] <= mid) {
			if (dis[i] >= l) {
				tim++;
				if (tim <= m) {
					return 1;
				} else {
					return 0;
				}
			} else {
				
			}
		} else {
			tim++;
			ni = i - 1;
			i--;
		}
	}
	return 0;
}
int main() {
	int i, left, right, mid, x;
	while (scanf("%d%d%d", &l, &n, &m) != EOF) {
		for (i = 0; i < n; i++) {
			scanf("%d", &dis[i]);
		}
		dis[n] = l;
		n++;
		dis[n] = 0;
		n++;
		sort(dis, dis + n);
		left = 0, right = l;
		while (left < right) {
			mid = (left + right) >> 1;
			if (test(mid)) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		printf("%d\n", left);
	}
}
