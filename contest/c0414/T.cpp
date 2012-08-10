#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	int n = (int)1e7;
	int c = 4;
	int sum = 0;
	int ans = 0;
	srand(time(0));
	for (int i = 0; i < c*n; ++i) {
		sum = (sum + 1);
		//ans = (ans + 1) % (1+rand());
	}
	printf("%d\n", sum);
	return 0;
}

