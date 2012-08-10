#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char st[1000000+100];
int top;
char s[1000000+100];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%s", s);
		top = -1;
		char * ps = s;
		int ans = 0;
		while (*ps) {
			if (*ps == '(') {
				st[++top] = *ps;
			} else {
				if (st[top] == '(') {
					ans += 2;
					--top;
				}
			}
			++ps;
		}
		printf("%d\n", ans);
	}
	return 0;
}

