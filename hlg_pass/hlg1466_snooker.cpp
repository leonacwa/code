#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

int a[1005];

int main() {
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		/*
		printf(".");
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
			if (i % 4 == 0) printf(", ");
		}
		puts("");
		*/
		int s[2] ={0, 0}, l = 0, red = 15, t, t27 = 27, i;
		bool in[8];
		memset(in, true, sizeof(in[0]) * 8);
		for (i = 1; i <= n; ++i) {
			s[l] += a[i];

			if (red == 0 && in[a[i]]) {
				t27 -= a[i];
				in[a[i]] = false;
			}
			if (a[i] == 1) --red;
			t = red * 8 + t27;

			if (a[i] == 0) {
				if (abs(s[0] - s[1]) > t) break;
				l = 1 - l;
			} else if (a[i] == 1) {
				if (s[l] > s[1-l] && s[1-l]+t < s[l]) break;
				if (s[l] < s[1-l] && s[l]+t+7 < s[1-l]) break;
			} else {
				if (abs(s[0] - s[1]) > t) break;
			}
		}
		if (i > n) i = n;
		//printf("ans %d %d  :", s[0], s[1]);
		printf("%d\n", i);
	}
	return 0;
}
