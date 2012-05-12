#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct Pig {
	int id;
	long long weight;
};
struct City {
	int id;
	long long distance, price, profit;
};
bool cmpPig(const Pig &a, const Pig &b) {
	return a.weight > b.weight;
}
bool cmpCityProfit(const City &a, const City &b) {
	return a.profit > b.profit;
};

int n, t;
Pig p[1005];
City c[1005];
int ans[1005];

int main()
{
	while (EOF != scanf("%d %d", &n, &t)) {
		for (int i = 0; i < n; ++i) {
			scanf("%I64d", &p[i].weight);
			p[i].id = i;
		}
		for (int i = 0; i < n; ++i) {
			scanf("%I64d", &c[i].distance);
			c[i].id = i;
		}
		for (int i = 0; i < n; ++i) {
			scanf("%I64d", &c[i].price);
			c[i].profit = c[i].price - c[i].distance * t;
		}
		sort(p, p+n, cmpPig);
		sort(c, c+n, cmpCityProfit);
		for (int i = 0; i < n; ++i) {
			ans[c[i].id] = p[i].id;
		}
		for (int i = 0; i < n-1; ++i) {
			printf("%d ", ans[i] + 1);
		}
		printf("%d\n", ans[n-1] + 1);
	}
	return 0;
}