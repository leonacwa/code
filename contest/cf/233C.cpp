/* C. Cycles
 * */
#include <iostream>
using namespace std;

int cn3(int n) {
	return n * (n - 1) * (n - 2) / 6;
}

int cn2(int n) {
	return n * (n - 1) / 2;
}

int g[103][102] = {0};

int main() {
	int n, k;
	cin >> k;
	for (n = 3; cn3(n+1) <= k; ++n) ;
	for (int i = 0; i < n; ++i) {
		g[i][i] = 0;
		for (int j = i+1; j < n; ++j) {
			g[i][j] = g[j][i] = 1;
		}
	}
	k -= cn3(n);
	for (; k > 0; ++n) {
		int n2 = 1;
		for (; k - cn2(n2+1) >= 0; ++n2) ;
		k -= cn2(n2);
		for (int i = 0; i < n2; ++i) g[i][n] = g[n][i] = 1;
	}
	cout << n << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << g[i][j];
		}
		cout << endl;
	}
	return 0;
}
