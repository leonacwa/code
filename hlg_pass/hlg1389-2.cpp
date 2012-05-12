#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 1000000 + 100;
int c[NN];
char s[NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int k;
		scanf("%d\n%s", &k, s);
		long long ans = 0;
		int sum = 0;
		c[0] = 0;
		for (int i = 0; s[i]; ++i) {
			if (8 <= i && 'J' == s[i-8] && 'i' == s[i-7] && 'a' == s[i-6] && 'o' == s[i-5] && 
					'z' == s[i-4] && 'h'== s[i-3] && 'u' == s[i-2] && 'V' == s[i-1] && '5' == s[i]) {
				++sum;
				c[sum] = 0;
			}
			++c[sum];
			if (k == 0) {
				if (sum - k == 0) {
					ans += c[sum - k];
				} else if (sum - k > 0) {
					ans += c[sum - k] + 7;
				}
			} else {
				if (sum - k == 0) {
					ans += c[sum - k] - 7;
				} else if (sum - k > 0) {
					ans += c[sum - k];
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

