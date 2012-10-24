#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int n, a[3];
	char str[256];
	while (EOF != scanf("%d%d%d%s", &n, &a[0], &a[1], str)) {
		a[2] = n - a[0] - a[1];
		if (!(a[0] <= n && a[1] <= n && a[2] >= 0 && a[2] <= n)) {
			puts("-1");
			continue;
		}
		int a1[3]= {0, 0, 0};
		for (int i = 0; i < n; ++i) {
			++a1[str[i] - '0'];
		}
		int b[3];
		int ans = 0, k = 0, sum = 0;
		for(int i = 0; i < 3; ++i) {
			b[i] = abs(a[i] - a1[i]);
			sum += b[i];
			if (ans < b[i]) {
				ans = b[i];
				k = i;
			}
			if (a[i] < a1[i]) {
				for (int j = n-1; j >= 0; --j) {
					if (str[j] - '0' == i && b[i] > 0) {
						str[j] = '-';
						if (0 == --b[i]) break;
					}
				}
			}
		}
		for (int i = 0; i < 3; ++i) {
			if (a[i] > a1[i]) {
				for (int j = n-1; j >= 0; --j) {
					if (str[j] == '-' && b[i] > 0) {
						str[j] = '0' + i;
						if (0 == --b[i]) break;
					}
				}
			}
		}
		if (sum-ans != ans) puts("-1");
		else printf("%d\n%s\n", ans, str);
	}
	return 0;
}
