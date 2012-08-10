#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
using namespace std;

int n, c, k;
int p[50000+100];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d", &n, &c, &k);
		for (int i = 1; i <= n; ++i) {
			if (i != c) {
				scanf("%d", &p[i]);
			} else {
				p[i] = 0;
			}
		}
		int kk = k, pr = p[k], prr = p[p[k]];
		while (pr) {
			p[pr] = kk;
			kk = pr;
			pr = prr;
			prr = p[pr];
		}
		int i = 1;
		for (; i <= n; ++i) {
			if (i != k) {
				printf("%d", p[i]);
				++i;
				break;
			}
		}
		for (; i <= n; ++i) {
			if (i != k) {
				printf(" %d", p[i]);
			}
		}
		puts("");
	}
	return 0;
}

