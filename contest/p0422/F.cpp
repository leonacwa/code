#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int top;
char st[32][256];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int n;
		scanf("%d", &n);
		top = 0;
		strcpy(st[0], "");
		for (int i = 0; i < n; ++i) {
			char cmd[256], path[256];
			scanf("%s", cmd);
			if (0 == strcmp(cmd, "pwd")) {
				for (int i = 0; i <= top; ++i) {
					printf("%s/", st[i]);
				}
				puts("");
			} else {
				char dir[256];
				int l = 0;
				scanf("%s", path);
				for (int i = 0; ; ++i) {
					if ('/' != path[i] && path[i]) {
						dir[l++] = path[i];
					} else {
						dir[l] = 0;
						if (l == 0) {
							top = 0;
						} else if(0 == strcmp("..", dir)) {
							if (top) {
								--top;
							}
						} else {
							++top;
							strcpy(st[top], dir);
						}
						l = 0;
					}
					if (path[i] == 0) break;
				}
			}
		}
	}
	return 0;
}


