#define DEBUG
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class TwoRectangles {
	public:
		string describeIntersection(vector<int> a, vector<int> b) {
			if (a[0] > b[0]) swap(a, b);
			int lx = max(a[0], b[0]), ly = max(a[1], b[1]);
			int rx = min(a[2], b[2]), ry = min(a[3], b[3]);
			if (rx < lx || ry < ly) return "none";
			int ans = (rx - lx) * (ry - ly);
			if (ans > 0) return "rectangle";
			if (lx == rx && ly == ry) return "point";
			return "segment";
		}
};
#ifdef DEBUG
int main()
{
	return 0;
}
#endif

