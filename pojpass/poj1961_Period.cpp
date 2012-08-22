#include <stdio.h>

const int MAXN = 1000000+5;
char s[MAXN];
int next[MAXN];

int make_next(char s[], int next[])
{
	int i, k = -1;
	next[0] = -1;
	for (i = 1; s[i]; i++) {
		while (k >= 0 && s[k+1] != s[i]) {
			k = next[k];
		}
		if (s[k+1] == s[i]) {
			k++;
		}
		next[i] = k;
	}
	return i;
}

int main()
{
	int n, cs = 0;
	while (EOF != scanf("%d", &n) && n > 0) {
		if (cs != 0) {
			puts("");
		}
		printf("Test case #%d\n", ++cs);
		scanf("%s", s);
		make_next(s, next);
		for (int i = 1; s[i]; i++) {
			int k = 0, l1 = i, l2 = i - next[i];
			/*
			while (l1 >= 0 && (l1 - next[l1] == l2) && ((next[l1] + 1) % l2 == 0)) {
				k++;
				l1 = next[l1];
			}
			*/
			if ((l1+1) % l2 == 0) {
				k = (l1+1) / l2;
			}
			if (k >= 2) {
				printf("%d %d\n", i+1, k);
			}
		}
	}
	return 0;
}

