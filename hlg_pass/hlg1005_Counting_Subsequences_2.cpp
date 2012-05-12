#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1000000;

struct FS {
	int sum, id;
	bool operator < (const FS& b) const {
		if (sum == b.sum) return id < b.id;
		return sum < b.sum;
	}
};
FS f[MAXN];
int a[MAXN];

int bs(int l, int  r, int sum)
{
	while (l < r) {
		int mid = (r-l) / 2 + l;
		if (f[mid].sum < sum) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	if (f[l].sum != sum) {
		return -1;
	}
	while (l > 0 && f[l-1].sum == f[l].sum) {
		l--;
	}
	return l;
}

int main()
{
	int caseN;
	scanf("%d", &caseN);
	while (caseN--) {
		int n;
		scanf("%d", &n);
		f[0].sum = 0;
		f[0].id = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			f[i].sum = f[i-1].sum + a[i];
			f[i].id = i;
		}
		sort(f, f+n+1);
		int ans = 0, sum = 0;
		for (int i = 1; i <= n; i++) {
			sum += a[i];
			int p = bs(0, n, sum-47);
			if (p != -1) {
				int inc = 0;
				for (int j = p; f[j].id < i && f[j].sum == sum-47; j++) {
					inc++;
				}
				ans += inc;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

