#include <stdio.h>

int main()
{
	char s[128];
	while (gets(s)) {
		int cnt = 0, ans = 0;
		char ch = 0;
		for (int i = 0; s[i]; i++) {
			if (ch != s[i]) {
				ans += cnt?1:0;
				ch = s[i];
				cnt = 1;
			} else {
				cnt++;
			}
			if (cnt == 5) {
				ans += cnt?1:0;
				ch = 0;
				cnt = 0;
			}
		}
		ans += cnt?1:0;
		printf("%d\n", ans);
	}
	return 0;
}

