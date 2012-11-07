/*
 * CF 239 A.Two Bags of Potatoes
 * */
#include <iostream>
using namespace std;

int main() {
	int y, k, n;
	while (cin >> y >> k >> n) {
		int cnt = 0;
		int nk = n / k;
		for (int i = 1; i <= nk; ++i) {
			if (i * k - y <= 0) continue;
			if (cnt == 0) {
				cout << i * k - y;
			} else {
				cout << " " << i * k - y;
			}
			++cnt;
		}
		if (cnt == 0) cout << "-1" << endl;
		else cout << endl;
	}
	return 0;
}
