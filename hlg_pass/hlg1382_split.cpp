#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int NN = 8;

struct Point {
	int x, y;
} pt[NN];

bool used[NN];

int pxmult(int p1, int p2, int p3, int p4)
{
	int x1 = pt[p2].x - pt[p1].x, y1 = pt[p2].y - pt[p1].y, x2 = pt[p4].x - pt[p3].x, y2 = pt[p4].y - pt[p3].y;
	return x1 * x2 + y1 * y2;
}

bool can(bool sq)
{
	bool ret = false;
	int p1;
	for (p1 = 0; p1 < NN; ++p1) {
		if (used[p1] == sq) break;
	}
	for (int p2 = 0; p2 < NN; ++p2) {
		if (used[p2] == sq && p1 != p2) {
			int p3 = -1, p4 = -1;
			for (int i = 0; i < NN; ++i) {
				if (used[i] == sq && i != p1 && i != p2) {
					if (p3 == -1) {
						p3 = i;
					} else {
						p4 = i;
						break;
					}
				}
			}
			if ((!sq || pxmult(p1, p2, p3, p4) == 0) && pxmult(p1, p3, p1, p4) == 0 && pxmult(p2, p3, p2, p4) == 0) {
				ret = true;
				break;
			}
		}
	}
	return ret;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		for (int i = 0; i < NN; ++i) {
			scanf("%d %d", &pt[i].x, &pt[i].y);
		}
		memset(used, 0, sizeof(used));
		bool ans = false;
		for (int i1 = 0; i1 < NN; ++i1) {
			used[i1] = true;
			for (int i2 = i1 + 1; i2 < NN; ++i2) {
				used[i2] = true;
				for (int i3 = i2 + 1; i3 < NN; ++i3) {
					used[i3] = true;
					for (int i4 = i3 + 1; i4 < NN; ++i4) {
						used[i4] = true;
						ans = (can(true) && can(false));
						if (ans) goto PrintAns;
						used[i4] = false;
					}
					used[i3] = false;
				}
				used[i2] = false;
			}
			used[i1] = false;
		}
PrintAns:
		puts(ans ? "YES" : "NO");
	}
	return 0;
}

