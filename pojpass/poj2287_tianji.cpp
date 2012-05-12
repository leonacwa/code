/*  Greedy
 *  */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;
const int NN = 2005;
int n;
int s1[NN], s2[NN];

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) scanf("%d", &s1[i]);
		for (int i = 0; i < n; ++i) scanf("%d", &s2[i]);
		sort(s1, s1+n, greater<int>());
		sort(s2, s2+n, greater<int>());
		int f1 = 0, r1 = n - 1, f2 = 0, r2 = n - 1, ans = 0;
		while (f1 <= r1) {
			if (s1[f1] < s2[f2]) {
				--ans;
				--r1;
				++f2;
			} else if (s1[f1] > s2[f2]) {
				++ans;
				++f1;
				++f2;
			} else {
				if (s1[r1] > s2[r2]) {
					++ans;
					--r1;
					--r2;
				} else {
					if (s1[r1] < s2[f2]) {
						--ans;
					}
					--r1;
					++f2;
				}
			}
		}
		printf("%d\n", ans * 200);
	}
	return 0;
}

