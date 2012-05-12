#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
};

bool cmpxy(const Point &a, const Point &b) {
	if (a.x != b.x) return a.x > b.x;
	return a.y > b.y;
}

int n;
Point plist[50000+5];

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &plist[i].x, &plist[i].y);
		}
		sort(plist, plist + n, cmpxy);
		int ans = 1;
		int y = plist[0].y;
		int x = plist[0].x;
		for (int i = 1; i < n; ++i) {
			if (plist[i].x < x) {
				x = plist[i].x;
				if (plist[i].y > y) {
					y = plist[i].y;
					++ans;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

