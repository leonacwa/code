/* 扩展KMP
 * 稍微简化了一些
 * poj2185测的时候比extendKMP.cpp慢一些
 * */

#include <stdio.h>
#include <string.h>

void extend_kmp(char s[], int ext[], char t[], int next[]) {
	int i, j, p, k;
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
}

int main()
{
	return 0;
}
