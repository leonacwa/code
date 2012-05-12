/*
ID:freeleo1
LANG:C
TASK:dualpal
*/
#include <stdio.h>
#include <string.h>

char num[21] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};

int num_str(int x, int B, char* s)
{
	int sl = 0;
	while (x) {
		s[sl++] = num[x % B];
		x /= B;
	}
	s[sl] = 0;
	return sl;
}

int is_dualpal(int x)
{
	char s[256];
	int i, sl, B, pal, cnt = 0;
	for (B = 2; B <= 10; ++B) {
		sl = num_str(x, B, s);
		pal = 1;
		if (sl >= 2) 
			for (i = sl/2 - 1; i >= 0 && pal; --i) if (s[i] != s[sl-i-1]) pal = 0;
		if (pal) cnt++;
		if (cnt >= 2) return 1;
	}
	return 0;
}

int main()
{
	freopen("dualpal.in", "r", stdin);
	freopen("dualpal.out", "w", stdout);
	int i, n, s;
	scanf("%d %d", &n, &s);
	for (i = s+1; n; ++i) {
		if (is_dualpal(i)) printf("%d\n", i), n--;
	}
	fclose(stdout);
	return 0;
}

