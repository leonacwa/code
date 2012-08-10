#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct Day {
	int p, d;
};

bool cmpSmallPD(const Day &a, const Day &b) {
	if (a.p != b.p) {
		return a.p < b.p;
	}
	return a.d < b.d;
}
bool cmpSmallD(const Day &a, const Day &b) {
	return a.d < b.d;
}
bool cmpLargePD(const Day &a, const Day &b) {
	if (a.p != b.p) {
		return a.p > b.p;
	}
	return a.d > b.d;
}
bool cmpLargeD(const Day &a, const Day &b) {
	return a.d > b.d;
}

Day st[1000000+5];
Day tmp_st[1000000+5];
int n, k1, k2;

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d %d", &n, &k1, &k2)) {
		if (n == 0 && k1 == 0 && k2 == 0) break;	
		for (int i = 0; i < n; ++i) {
			scanf("%d", &st[i].p);
			st[i].d = i+1;
		}
		printf("Case %d\n", ++nCase);
		sort(st, st+n, cmpSmallPD);

		for (int i = 0; i < k1; ++i) {
			tmp_st[i] = st[i];
		}
		sort(tmp_st, tmp_st + k1, cmpSmallD);
		for (int i = 0 ; i < k1 - 1; ++i) {
			printf("%d ", tmp_st[i].d);
		}
		printf("%d\n", tmp_st[k1-1].d);

		for (int i = 0; i < k2; ++i) {
			tmp_st[i] = st[n - i - 1];
		}
		sort(tmp_st, tmp_st + k2, cmpLargeD);
		for (int i = 0 ; i < k2 - 1; ++i) {
			printf("%d ", tmp_st[i].d);
		}
		printf("%d\n", tmp_st[k2-1].d);
	}
	return 0;
}

