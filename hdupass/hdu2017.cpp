#include <iostream>
using namespace std;

int main()
{
	int n, cnt;
	char ch;
	cin >> n;
	cin.ignore();
	while (n--) {
		cnt = 0;
		while (cin.get(ch) && ch != '\n') {
			if ('0' <= ch && ch <= '9')
				cnt++;
		}
		cout << cnt << endl;
	}
	return 0;
}

