#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		char s[32];
		scanf("%s", s);
		bool yes = true;
		for (int i = 0; s[i]; ++i) {
			if (s[i] != '4' && s[i] != '7') {
				yes = false;
				break;
			}
		}
		printf("%s\n", yes ? "YES" : "NO");
	}
	return 0;
}

