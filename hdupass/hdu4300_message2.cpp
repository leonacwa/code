/* hdu4300
 * */

#include <stdio.h>
#include <string.h>

void extend_kmp(char s[], int ext[], char t[], int next[]) {
	int i, j, a, p, k,len;
	int ls = strlen(s), lt = strlen(t);
	next[0] = lt;
	k = 1;
	j = -1;
	for (i = 1; i < lt; ++i, --j) {
		if (j < 0 || i + next[i - k] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < lt && t[p] == t[j]) ++j, ++p;
			next[i] = j, k = i;
		}
		else next[i] = next[i - k];
	}
	j = -1;
	for (i = 0; i < ls; ++i, --j) {
		if (j < 0 || i + next[i - k] >= p) {
			if (j < 0) j = 0, p = i;
			while (p < ls && j < lt && s[p] == t[j]) ++j, ++p;
			ext[i] = j, k = i;
		}
		else ext[i] = next[i - k];
	}
	/*
	puts(s);
	puts(t);
	for (int i = 0; i < ls; ++i) printf("%d ", ext[i]); puts(" ");
	for (int i = 0; i < lt; ++i) printf("%d ", next[i]); puts(" ");
	*/
}

const int MAXN = 200005;
char tb[MAXN], s[MAXN], t[MAXN];
int next[MAXN], ext[MAXN];

int main()
{
	int nT;
	scanf("%d", &nT);
	while (nT--) {
		scanf("%s%s", t, s);
		for (int i = 0; t[i]; ++i) {
			tb[t[i]] = 'a' + i;
		}
		int ls = strlen(s);
		for (int i = 0; i < ls; ++i) {
			t[i] = tb[s[i]];
		}
		t[ls] = 0;
		extend_kmp(s, ext, t, next);
		int i;
		for (i = 0; i < ls; ++i) {
			if (i + ext[i] == ls && i >= ext[i]) {
				break;
			}
		}
		//printf("i %d\n", i);
		for (int j = 0; j < i; ++j) {
			s[i+j] = tb[s[j]];
		}
		s[i*2] = 0;
		puts(s);
	}
	return 0;
}
