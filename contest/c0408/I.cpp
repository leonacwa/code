#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

const int NN = 1000000;
int prm_cnt;
bool is[NN+1];
int prm[NN+1];
void getprm()
{
	memset(is, true, sizeof(is));
	is[0] = is[1] = false;
	prm_cnt = 0;
	int n = (int)sqrt(NN+1.0);
	for (int i = 2; i <= n; ++i) {
		if (!is[i]) continue;
		prm[prm_cnt++] = i;
		for (int j = i + i; j <= NN && j > 0; j += i) {
			is[j] = false;
		}
	}
	for (int i = n+1; i <= NN; ++i) {
		if (is[i]) {
			prm[prm_cnt++] = i;
		}
	}
}

int gcd(int a, int b)
{
	int t;
	while (b) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int nFac;
long long fac[NN];

void getFactor(long long f)
{
	nFac = 1;
	fac[0] = 1;
	for (int i = 0; i < prm_cnt && f > 1; ++i) {
		int l = 0, r;
		while (f % prm[i] == 0) {
			r = nFac;
			for (int j = l; j < r; ++j) {
				fac[nFac++] = fac[j] * prm[i];
			}
			l = r;
			f /= prm[i];
		}
	}
	if (f > 1) {
		int r = nFac;
		for (int j = 0; j < r; ++j) {
			fac[nFac++] = fac[j] * f;
		}
	}
}

int main()
{
	int n, m, cnt, nCase = 0;
	getprm();
	while (EOF != scanf("%d %d", &m, &n)) {
		if (m > n) {
			cnt = 0;
		} else if (m == n) {
			cnt = 1;
		} else {
			int g = gcd(n, m);
			n /= g, m /= g;
			nFac = 0;
			long long nn = n;
			nn *= n;
			getFactor(nn);
			cnt = 0;
			for (int i = 0; i < nFac; ++i) {
				long long a = fac[i], b;
				b = nn / a;
				if (a > b) continue;
				if ((a + n) % m == 0 && (b + n) % m == 0) {
					++cnt;
				}
			}
		}
		printf("Scenario #%d\n", ++nCase);
		if (cnt == 0) {
			printf("No solution\n\n");
		} else if (cnt == 1) {
			printf("Only one solution\n\n");
		} else {
			printf("Find %d solutions\n\n", cnt);
		}
	}
	return 0;
}

