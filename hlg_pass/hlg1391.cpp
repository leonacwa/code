#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		puts((n - 1) % 4 == 0 ? "Orz" : "JiaozhuV5");
	}
	return 0;
}

