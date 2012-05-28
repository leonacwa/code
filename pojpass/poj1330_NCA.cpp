#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 10000 + 10;

int P[MAXN];
int L[MAXN];

void init(int x)
{
	if (P[x] == x) {
		L[x] = 0;
	} else {
		init(P[x]);
		L[x] = L[P[x]] + 1;
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i <= n; ++i) {
			P[i] = i;
		}
		int a, b;
		for (int i = 1; i < n; ++i) {
			scanf("%d %d", &a, &b);
			P[b] = a;
		}
		scanf("%d %d", &a, &b);
		init(a);
		init(b);
		while (a != b) {
			if (L[a] < L[b]) {
				b = P[b];
			} else {
				a = P[a];
			}
		}
		printf("%d\n", a);
	}
	return 0;
}

