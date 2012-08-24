#include <iostream>
using namespace std;

int abs_int(int x) {
	return x < 0? -x:x;
}
int main()
{
	int n;
	int a[100];
	while (cin >> n && n != 0) {
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				if (abs_int(a[i]) < abs_int(a[j])) {
					int t = a[i];
					a[i] = a[j];
					a[j] = t;
				}
			}
		}
		cout << a[0];
		for (int i = 1; i < n; ++i) {
			cout << " " << a[i];
		}
		cout << endl;
	}
	return 0;
}
