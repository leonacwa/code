/*
2011 ACM/ICPC Fuzhou Online
War
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
struct Cell {
	int d, t;
};
Cell ce[100000+1];
bool cmp_cell(const Cell &a, const Cell &b)
{
	if (a.t == b.t) return a.d > b.d;
	return a.t > b.t;
}

int main()
{
	int cs,  nCase;
	int ts, remain, i, n;
	scanf("%d", &nCase);
	for (cs = 1; cs <= nCase; ++cs) {
		scanf("%d", &n);
		for (i = 0; i < n; ++i) scanf("%d %d", &ce[i].d, &ce[i].t);
		sort(ce, ce+n, cmp_cell);
		ts = 0;
		remain = 0;
		for (i = 0; i < n; ++i) {
			ts += ce[i].d;
			if (remain < ce[i].d) {
				remain = 0;
			} else {
				remain -= ce[i].d;
			}
			if (remain < ce[i].t) {
				remain = ce[i].t;
			}
			//printf("%d %d, %d %d\n", ce[i].d, ce[i].t, ts, remain);
		}
		ts += remain;
		printf("Case %d: %d\n", cs, ts);
	}
	return 0;
}
