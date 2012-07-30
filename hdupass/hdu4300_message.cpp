/* hdu4300
 * */

#include <stdio.h>
#include <string.h>

void extend_kmp(char s[], int ext[], char t[], int next[]) {
	int i, j, a, p, k,len;
	int ls = strlen(s), lt = strlen(t);
	next[0] = lt;
	j = 0;
	while (1 + j < lt && t[1+j] == t[j]) ++j;
	next[1] = j;
	k = 1;
	for (i = 2; i < lt; ++i) {
		p = k + next[k] - 1;
		len = next[i - k];
		if (i + len - 1 < p) next[i] = len;
		else {
			j = p - i + 1;
			if (j < 0) j = 0;
			while (i+j < lt && t[i+j] == t[j]) ++j;
			next[i] = j;
			k = i;
		}
	}
	j = 0;
	while (j < ls && j < lt && s[j] == t[j]) ++j;
	ext[0] = j;
	k = 0;
	for (i = 1; i < ls; ++i) {
		p = k + ext[k] - 1;
		len = next[i - k];
		if (i + len - 1 < p) ext[i] = len;
		else {
			j = p - i + 1;
			if (j < 0) j = 0;
			while (i + j < ls && j < lt && s[i+j] == t[j]) ++j;
			ext[i] = j;
			k = i;
		}
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
