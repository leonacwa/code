#include <stdio.h>
#include <string.h>

char str[10][61];
char ans[61];
int m;

int main()
{
	int nTest, i, j, k, len;
	char ch;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d", &m);
		for (i = 0; i < m; ++i) {
			scanf("%s", str[i]);
		}
		len = 0;
		for (i = 60; i >= 3; --i) {
			for (j = 0; i + j <= 60; ++j) {
				ch = str[0][j+i];
				str[0][j+i] = 0;
				for (k = 1; k < m; ++k) {
					if (NULL == strstr(str[k], str[0]+j)) {
						break;
					}
				}
				if (k == m) {
					if (len == 0 || strcmp(ans, str[0]+j) > 0) {
						strcpy(ans, str[0]+j);
						len = i;
					}
				}
				str[0][j+i] = ch;
			}
			if (len > 0) {
				break;
			}
		}
		if (len == 0) {
			puts("no significant commonalities");
		} else {
			puts(ans);
		}
	}
	return 0;
}

