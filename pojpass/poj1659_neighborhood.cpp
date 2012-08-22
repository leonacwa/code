#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 11;
struct Node {
	int d, seq;
};
bool cmpd(const Node &a, const Node &b) {
	if (a.d == b.d) return a.seq < b.seq;
	return a.d > b.d;
}
Node f[NN];
bool mat[NN][NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &f[i].d);
			f[i].seq = i;
		}
		memset(mat, 0, sizeof(mat));
		bool can = true;
		int i = 0;
		while (can && i < n) {
			sort(f+i, f+n, cmpd);
			if (f[i].d <= n-i-1) {
				for (int j = i+1; j <= i+f[i].d; ++j) {
					if (f[j].d <= 0) {
						can = false;
						break;
					} else {
						--f[j].d;
						mat[f[i].seq][f[j].seq] = mat[f[j].seq][f[i].seq] = true;
					}
				}
				++i;
			} else {
				can = false;
			}
		}
		if (false == can) {
			printf("NO\n");
		} else {
			printf("YES\n");
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n - 1; ++j) {
					printf("%d ", mat[i][j] ? 1 : 0);
				}
				printf("%d\n", mat[i][n - 1] ? 1 : 0);
			}
		}
		if (nTest) {
			puts("");
		}
	}
	return 0;
}

