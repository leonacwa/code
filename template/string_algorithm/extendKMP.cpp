/* 扩展KMP
 * 这个代码较多，不过好像比extendKMP2.cpp快些，poj2185测的
 * */

#include <stdio.h>
#include <string.h>

void extend_kmp(char s[], int ext[], char t[], int next[]) {
	int i, j, a, p, k,len;
	int ls = strlen(s), lt = strlen(t);
	next[0] = lt;
	j = 0;
	while (1+j < lt && t[j] == t[1+j]) ++j;
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
}

int main()
{
	return 0;
}
