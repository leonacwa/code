/* B.Effective Approach
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int a[100005];
int fir[100005], fin[100005];

int main() {
	int n;
	while (cin >> n) {
		memset(fir, -1, sizeof(fir));
		memset(fin, -1, sizeof(fin));
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			if (fir[a[i]] == -1) fir[a[i]] = i;
			fin[a[i]] = n - i + 1;
		}
		int m;
		long long s = 0, p = 0;
		cin >> m;
		while (m--) {
			int b;
			cin >> b;
			if (fir[b] == -1) {
				s += n;
			} else {
				s += fir[b];
			}
			if (fin[b] == -1) {
				p += n;
			} else {
				p += fin[b];
			}
		}
		cout << s << " " << p << endl;
	}
	return 0;
}
