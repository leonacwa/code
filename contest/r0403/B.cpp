#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int check(int a[])
{
	if (a[0] + a[1] > a[2] && a[1] - a[0] < a[2]) return 1;
	if (a[0] + a[1] == a[2]) return 0;
	return -1;
}

int main()
{
	int a[4], b[4];
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d %d", a, a+1, a+2, a+3);
		sort(a, a+4);
		int ans = -1;
		b[0] = a[0], b[1] = a[1], b[2] = a[2];
		ans = max(ans, check(b));
		b[0] = a[0], b[1] = a[1], b[2] = a[3];
		ans = max(ans, check(b));
		b[0] = a[0], b[1] = a[2], b[2] = a[3];
		ans = max(ans, check(b));
		b[0] = a[1], b[1] = a[2], b[2] = a[3];
		ans = max(ans, check(b));
		if (ans == 1) puts("T");
		else if (ans == 0) puts("S");
		else puts("I");
	}
	return 0;
}

