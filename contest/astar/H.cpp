#include <cstdio>
const int MAXN = 100000 + 5;
char s[MAXN];
int next[MAXN];
char ans[MAXN];

int make_next(char s[], int next[])
{
	int i, j = -1;
	next[0] = -1;
	for (i = 1; s[i]; i++) {
		while (j >= 0 && s[j+1] != s[i]) {
			j = next[j];
		}
		if (s[j+1] == s[i]) {
			j++;
		}
		next[i] = j;
	}
	return i;
}

int main()
{
	while (EOF != scanf("%s", s) && !(s[0] == '.' && s[1] == '\0')) {
		int sl = make_next(s, next);
		for (int i = sl - 1; i >= 0; --i) {
		}
		printf("%d\n", ans);
	}
	return 0;
}

