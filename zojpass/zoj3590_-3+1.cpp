#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	long long c[3], ll, ans, ll2, t;
	int a, n;
	//while (cin >> n) {
	while (EOF != scanf("%d", &n)) {
		c[0] = 0;
		c[1] = 0;
		c[2] = 0;
		ans = 0;
		ll = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a);
			//cin >> a;
			c[a % 3]++;
			ll += a / 3;
		}
		ans = ll;
		while (ll > 0) {
			t = min(c[2], ll); 
			if (t > 0) {
				ans += t;
				ll = ll - t + t;
				c[2] -= t;
				c[0] += t;
			} else {
				t = min(c[1], ll / 2); 
				if (t > 0) {
					ans += t;
					ll = ll - 2 * t + t;
					c[1] -= t;
					c[0] += t;
				} else {
					t = min(c[0], ll / 3);
					ans += t;
					ll =  ll - 3 * t + t;
					if ((c[2] > 0 && ll < 1) || (c[1] > 0 && ll < 2) || (c[2] == 0 && c[1] == 0 && ll < 3)) {
						break;
					}
				}
			}
		}
		printf("%lld\n", ans);
		//cout << ans << endl;
	}
	return 0;
}
