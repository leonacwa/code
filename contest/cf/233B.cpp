/* B. Non-square Equation
 * */
#include <cmath>
#include <iostream>
using namespace std;

typedef long long LL;

LL s(LL x) {
	LL r = 0;
	while (x) {
		r += x % 10;
		x /= 10;
	}
	return r;
}

LL f(LL x) {
	return x * x + s(x) * x;
}

int main() {
	LL n;
	while (cin >> n) {
		double rn = sqrt(n + 1.0);
		LL x, a = (LL)floor(rn - 1), b = (LL)ceil(rn + 1);
		if (a <= 0) a = 1;
		if (b <= 0) b = 2;
		//cout << " : " << a << " " << b << endl;
		for (x = a; x <= b; ++x) {
			if (f(x) == n) break;
		}
		if (x <= b) cout << x << endl;
		else cout << "-1" << endl;
	}
	return 0;
}
