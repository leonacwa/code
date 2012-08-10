#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int NN = 1000000 + 5;
bool is[NN];
int cnt_prm;
int prm[NN];

void getprm()
{
	memset(is, true, sizeof(is));
	is[0] = is[1] = false;
	int qn = (int)sqrt(NN) + 1;
	cnt_prm = 0;
	for (int i = 2; i <= qn; ++i) {
		if (!is[i]) continue;
		prm[cnt_prm++] = i;
		for (int j = i + i; j <= NN; j += i) {
			is[j] = false;
		}
	}
	for (int i = qn+1; i <= NN; ++i) {
		if (is[i]) {
			prm[cnt_prm++] = i;
		}
	}
}

int main()
{
	getprm();
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		long long n;
		scanf("%lld", &n);
		long long ans = 1;
		for (int i = 0; i < cnt_prm; ++i) {
			if (n % prm[i] == 0) {
				int cnt = 0;
				while (n % prm[i] == 0) {
					++cnt;
					n /= prm[i];
				}
				ans *= ((cnt << 1) | 1);
			}
			if (n == 1) {
				break;
			}
		}
		if (n > 1) {
			ans *= 3;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

