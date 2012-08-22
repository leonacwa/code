/*
ID:freeleo1
LANG:C
TASK:ride
*/
#include <stdio.h>

int main()
{
	char s[2][256];
	int a, b, i;
	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);
	scanf("%s", s[0]);
	scanf("%s", s[1]);
	a = b = 1;
	for (i = 0; s[0][i]; ++i) a *= s[0][i] - 'A' + 1;
	for (i = 0; s[1][i]; ++i) b *= s[1][i] - 'A' + 1;
	if (a % 47 == b % 47 ) printf("GO\n");
	else printf("STAY\n");
	fclose(stdout);
	return 0;
}
