#include <cstdio>
#include <cstring>
typedef long long int64;
const int64 MOD = 317000011;

int64 pow2(int64 a, int64 b, int64 _MOD = MOD)
{
	if (a == 0) return 0;
	if (b == 0) return 1;
	int64 r = 1;
	while (b) {
		if (b & 1) r = r * a % _MOD;
		a = a * a % _MOD;
		b >>= 1;
	}
	return r;
}

int64 pow3(int64 a, int64 b, int64 c)
{
	if (c == 0) return a;
	if (c == 1) return pow2(a, b);
	if (c&1) return pow2(pow3(pow3(a, b, c/2), b, c/2), b);
	else return pow3(pow3(a, b, c/2), b, c/2);
}

int64 pow3_2(int64 a, int64 b, int64 c)
{
	if (c == 0) return a;
	if (c == 1) return pow2(a, b);
	int64 bb = pow2(b, c, MOD-1);
	return pow2(a, bb) % MOD;
}


int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		//printf("%lld\n", pow3(a, b, c));
		printf("%lld\n", pow3_2(a, b, c));
		//printf("-%d\n", pow2(a,pow2(b, c)));
	}
	return 0;
}

