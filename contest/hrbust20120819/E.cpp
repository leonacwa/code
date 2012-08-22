#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int f[420][40];

int main() {
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	for (int i = 1; i <= 390; ++i) {
		for (int j = 1; j <= 39 && j <= i; ++j) {
			for (int k = 0; k < j && k <= i - j; ++k) {
				f[i][j] += f[i-j][k];
			}
		}
	}
	int n;
	while (cin >> n) {
		int sum = n * (n+1);
		if (sum % 4) puts("0");
		else {
			sum /= 4;
			cout << f[sum][n] << endl;
		}
	}
	return 0;
}
