#include <iostream>
using namespace std;

int main()
{
	int i;
	int c[56];
	c[1] = 1;
	c[2] = 2;
	c[3] = 3;
	for (i = 4; i < 55; ++i) {
		c[i] = c[i-1] + c[i-3];
	}
	while (cin >> i && i > 0){
		cout << c[i] << endl;
	}
	return 0;
}
