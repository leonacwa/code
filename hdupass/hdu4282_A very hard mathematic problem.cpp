/*HDU4282 A very hard mathematic problem
 * 数学题，暴力枚举，优化：减小枚举范围
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
typedef long long int64;

int64 q_pow(int64 n, int64 k) {
	int64 ans = 1;
	while(k) {
		if(k & 1) {
			ans *= n;
		}
		k >>= 1;
		n *= n;
	}
	return ans;
}

int64 f(int a, int b, int c, int x) {
	return q_pow(x, a) + b * x + c;
}

int test(int a, int b, int c, int l, int r) {
	int m;
	while (l <= r) {
		m = (l + r) >> 1;
		int64 res = f(a, b, c, m);
		if (res == 0) return m;
		if (res < 0) l = m + 1;
		else r = m -1;
	}
	return -1;
}

int main() {
	int k;
	while (EOF != scanf("%d", &k) && k) {
		int cnt = 0;
		for (int z = 2; z <= 30; ++z) {
			int max_x = (int)(pow(k/2.0, 1.0/z)+1);
			for (int x = 1; x <= max_x+1; ++x) {
				if (q_pow(x, z) + q_pow(x+1, z) + x * (x+1) > k) break;
				int xz = (int)q_pow(x, z);
				int y = (test(z, x*z, xz - k, x+1, (int)(pow(k+0.0, 1.0/z))));
				if (y > 0) {
					++cnt;
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
