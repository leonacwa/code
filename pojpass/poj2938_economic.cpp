#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct Call {
	char date[12];
	char num[17];
	char sign;
};
int n;
Call c[1005];

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%s %s %c", c[i].date, c[i].num, &c[i].sign);
		}
		strcpy(c[n].date, "00:00:00:00");
		int i = 0;
		int ans = 0;
		while (c[i].sign == '-' && i < n) ++i, ++ans;
		int pre = i;
		for (++i; i < n; ++i) {
			if (c[i].sign == '+') {
				pre = i;
			} else {
				int x = strcmp(c[pre].date, c[i].date);
				int y = strcmp(c[i].date, c[i+1].date);
				int z = strcmp(c[pre].date, c[i+1].date);
				if (x < 0 && y < 0) {
					++ans;
				} else if ((z >= 0) && (x >= 0 && y < 0 || x < 0 && y >= 0)) {
					++ans;
				} else {
					pre = i;
				}
			}
		}
		printf("%d\n", n - ans);
	}
	return 0;
}

