#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int a[4];
	while (EOF != scanf("%d %d %d", a, a+1, a+2)) {
		sort(a, a+3);
		printf("%d", a[2]);
		printf(" %d", a[1]);
		printf(" %d\n", a[0]);
	}
	return 0;
}
