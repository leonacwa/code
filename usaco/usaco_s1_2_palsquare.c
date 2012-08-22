/*
ID:freeleo1
LANG:C
TASK:palsquare 
*/
#include <stdio.h>
#include <string.h>

char num[21] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
char s[2][256];
int sl, B;

int num_str(int x, char* s)
{
	int sl = 0;
	while (x) {
		s[sl++] = num[x % B];
		x /= B;
	}
	s[sl] = 0;
	char c;
	for (x = sl/2-1; x >= 0; --x) {
		c = s[x];
		s[x] = s[sl-x-1];
		s[sl-x-1] = c;
	}
	return sl;
}

int is_pal(char *s)
{
	int i, sl = strlen(s);
	if (sl <= 1) return 1;
	for (i = sl/2 - 1; i >= 0; --i) if (s[i] != s[sl-i-1]) return 0;
	return 1;
}

int main()
{
	freopen("palsquare.in", "r", stdin);
	freopen("palsquare.out", "w", stdout);
	int i, n;
	scanf("%d", &B);
	for (n = 1; n <= 300; ++n) {
		num_str(n*n, s[1]);
		if (is_pal(s[1])) {
			num_str(n, s[0]);
			printf("%s %s\n", s[0], s[1]);
		}
	}
	fclose(stdout);
	return 0;
}

