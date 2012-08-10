#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int a[32];
int b[32];
int n;

bool same(int n, int a[]) {
	for (int i = 1; i < n; ++i) {
		if (a[i-1] != a[i]) {
			return false;
		}
	}
	return true;
}
bool equal(int n, int a[], int b[]) {
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d", &n) && n !=0) {
		++nCase;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		int cnt = 0;
		bool can = true;
		while (!same(n, b)) {
			int b0 = b[0];
			for (int i = 0; i < n - 1; ++i) {
				b[i] = abs(b[i] - b[i+1]);
			}
			b[n-1] = abs(b[n-1] - b0);
			++cnt;
			if (cnt > 1000 || equal(n, a, b)) {
				can = false;
				break;
			}
		}
		printf("Case %d: ", nCase);
		if (can) {
			printf("%d iterations\n", cnt);
		} else {
			printf("%s\n", "not attained");
		}
	}
	return 0;
}

