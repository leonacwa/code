#include <stdio.h>
#include <string.h>

char s1[1000+5], s2[1000+5];
int sl1, sl2;
int a[1000+5][1000+5];

int main()
{
	int nCase, i, j, t;
	scanf("%d", &nCase);
	while (nCase--) {
		scanf("%s", s1 + 1);
		scanf("%s", s2 + 1);
		sl1 = strlen(s1 + 1);
		sl2 = strlen(s2 + 1);
		memset(a, 0, sizeof(a));
		for (i = 1; i <= sl1; ++i) {
			a[i][0] = i;
		}
		for (i = 1; i <= sl2; ++i) {
			a[0][i] = i;
		}
		for (i = 1; i <= sl1; ++i) {
			for (j = 1; j <= sl2; ++j) {
				a[i][j] = a[i - 1][j - 1];
				if (s1[i] != s2[j]) {
					a[i][j]++;
				}
				t = a[i][j - 1] + 1;
				if (t < a[i][j]) {
					a[i][j] = t;
				}
				t = a[i - 1][j] + 1;
				if (t < a[i][j]) {
					a[i][j] = t;
				}
			}
		}
		printf("%d\n", a[sl1][sl2]);
	}
	return 0;
}

