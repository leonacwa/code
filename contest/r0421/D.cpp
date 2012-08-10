#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int cnt;
long long a47[2000];

void init()
{
	long limit = 1000000000LL;
	cnt = 2;
	a47[0] = 4;
	a47[1] = 7;
	int a = 0;
	while (a47[cnt-1] < limit) {
		int b = cnt;
		for (int i = a; i < b; ++i) {
			a47[cnt++] = a47[i] * 10 + 4;
			if (a47[cnt-1] >= limit) break;
			a47[cnt++] = a47[i] * 10 + 7;
			if (a47[cnt-1] >= limit) break;
		}
		a = b;
	}
	sort(a47, a47+cnt);
	/*
	printf("cnt:%d\n", cnt);
	for (int i = 0; i < cnt; ++i) {
		printf("%d ", a47[i]);
	}
	puts("");
	*/
}

int main()
{
	int nTest;
	init();
	scanf("%d", &nTest);
	while (nTest--) {
		int a, b;
		scanf("%d %d", &a, &b);
		long long sum = 0;
		long long x = 0;
		int i;
		for (i = 0; i < cnt; ++i) {
			if (a47[i] >= a) {
				x = a47[i];
				break;
			}
		}
		for (; i < cnt; ++i) {
			long long bb = min(x, (long long)b);
			sum += (long long) x * (bb - a + 1);
			//printf("a:%d, x:%d, bb:%d\n", a, x, bb);
			a = bb + 1;
			if (a > b) break;
			x = a47[i+1];
		}
		printf("%lld\n", sum);
	}
	return 0;
}

