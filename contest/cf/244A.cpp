/*
 * CF 244 A. Dividing Orange
 * */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int is[905];
bool vi[905];
int cnt[905];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; ++i) {
		int a;
		scanf("%d", &a);
		vi[a] = true;
		is[a] = i;
		++cnt[i];
	}
	for (int i = 1; i <= n*k; ++i) {
		if (!vi[i]) {
			for (int j = 1; j <= k; ++j) {
				if (cnt[j] < n) {
					is[i] = j;
					++cnt[j];
					vi[i] = true;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= k; ++i) {
		int oc = 0;
		for (int j = 1; oc < n && j <= n*k; ++j) {
			if (is[j] == i) {
				if (oc > 0) printf(" ");
				printf("%d", j);
				++oc;
			}
		}
		puts("");
	}
	return 0;
}
