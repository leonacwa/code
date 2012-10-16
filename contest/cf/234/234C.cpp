/*
 * CF 234 C. Weather
 * */
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

int n;
int t[MAXN];

int main() {
	freopen("input.txt", "r", stdin);	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	int neg = 0, zero = 0;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", t + i);
		if (t[i] < 0) ++neg;
		else if (t[i] == 0) ++zero;
	}
	int ans = n;
	int ns = 0, zs = 0;
	for (int i = 1; i < n; ++i) {
		if (t[i] < 0) ++ns;
		else if (t[i] == 0) ++zs;
		int tmp = i - ns + neg - ns + zero - zs;
		if (ans > tmp) ans = tmp;
	}
	printf("%d\n", ans);
	fclose(stdin);	fclose(stdout);
	return 0;
}
