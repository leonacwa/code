
typedef long long LL;
const LL MOD = 10007;
LL exgcd(LL a, LL b, LL &x, LL &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	LL g = exgcd(b, a % b, x, y);
	LL t = x;
	x = y;
	y = t - (a / b) * y;
	return g;
}

LL C(LL x, LL y) {
	LL ret = 1;
	if (x - y < y) y = x - y;
	for (LL i = 0; i < y; ++i) {
		ret = (ret * (x - i)) % MOD;
	}
	for (LL i = 2; i <= y; ++i) {
		LL xx, yy;
		exgcd(i, MOD, xx, yy); // gcd(a, b) = 1
		ret = (ret * xx) % MOD;
	}
	return ret;
}

