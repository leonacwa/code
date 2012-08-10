#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 100005;
struct Person {
	int h, a, e, f;
};
bool cmpa(const Person &a, const Person &b)
{
	if (a.a == b.a) return a.h < b.h;
	return a.a < b.a;
}
bool cmph(const Person &a, const Person &b)
{
	return a.h < b.h;
}

int n;
Person a[NN];
int f[NN];
int ans[NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].a);
			a[i].h = i;
			a[i].f = i;
		}
		sort(a+1, a+1+n, cmpa);
		a[1].e = -1;
		for (int i = 2; i <= n; ++i) {
			if (a[i].f < a[i-1].f) {
				a[i].f = a[i-1].f;
			}
			a[i].e = a[i].f - a[i].h - 1;
		}
		sort(a+1, a+1+n, cmph);
		for (int i = 1; i < n; ++i) {
			printf("%d ", a[i].e);
		}
		printf("%d\n", a[n].e);
	}
	return 0;
}

