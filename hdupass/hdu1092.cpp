#include <iostream>
using namespace std;

int main()
{
	int i, a, n, s;
	while (cin >> n && n > 0) {
		s = 0;
		for (i = 0 ; i < n; ++i) {
			cin >> a;
			s += a;
		}
		cout << s << endl;;
	}
    return 0;
}