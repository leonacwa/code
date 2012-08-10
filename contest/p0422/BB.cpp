#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		char s[10], t[10];
		scanf("%s", s);
		scanf("%s", t);
		int ans = max(abs(s[0] - t[0]), abs(s[1] - t[1]));
		printf("%d\n", ans);
	}
	return 0;
}


