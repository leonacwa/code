#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
typedef long long llong;

struct Point {
	llong x, y;
};

llong xmult(const Point &A, const Point &B) {
	return A.x * B.y - A.y * B.x;
}

bool cmpPoint(const Point &A, const Point &B) {
	llong xc = xmult(A, B);
	if (xc) return xc > 0;
	return A.x * A.x + A.y * A.y < B.x * B.x + B.y * B.y;
}

Point pt[MAXN], tpt[MAXN];
bool check(Point pt[], int n)
{
	for (int i = 0; i < n; ++i) {
		int c = 0;
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			tpt[c] = pt[j];
			tpt[c].x -= pt[i].x;
			tpt[c].y -= pt[i].y;
			++c;
		}
		sort(tpt, tpt + c, cmpPoint);
		for (int j = 1; j < c; ++j) {
			if (xmult(tpt[j-1], tpt[j]) == 0) return true;
		}
	}
	return false;
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%lld %lld", &pt[i].x, &pt[i].y);
		}
		char ch;
		if (n % 3) {
			ch = 'a';
		} else if (check(pt, n)) {
			ch = 'a';
		} else {
			ch = 'b';
		}
		printf("%c is the lucky boy.\n", ch);
	}
	return 0;
}

