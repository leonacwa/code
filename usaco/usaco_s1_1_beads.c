/*
ID:freeleo1
LANG:C
TASK:beads 
*/
#include <stdio.h>
#include <string.h>
int a[2], ans;
char s[800];

int main()
{
	int i, n, w;
	char p;
	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);
	scanf("%d %s", &n, s);
	memcpy(s+n, s, n);
	w = 0;
	p = 0;
	for (i = 0; s[i]; ++i) {
		if (s[i] == 'w') a[1]++, w++;
		else if (s[i] == p) a[1]++, w = 0;
		else {
			if (ans < a[0]+a[1]) ans = a[0]+a[1];
			a[0] = a[1] - w;
			a[1] = 1 + w;
			p = s[i];
			w = 0;
		}
	}
	if (a[0] + a[1] > ans) ans = a[0] + a[1];
	printf("%d\n", ans>n?n:ans);
	fclose(stdout);
	return 0;
}

