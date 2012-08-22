#include <stdio.h>
#include <string.h>

const int NN= 100000 + 5;

char *strrev(char *s)
{
	int i, ls = strlen(s) - 1;
	char ch;
	for (i = ls / 2; i >= 0; --i) {
		ch = s[i];
		s[i] = s[ls -i];
		s[ls - i] = ch;
	}
	return s;
}
int make_next(char s[], int next[])
{
	int i,  k = -1;
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
void kmp_count(char t[], char p[], int next[], long long cnt[])
{
	int i, j = -1;
	for (i = 0; t[i]; ++i) {
		while (j >= 0 && p[j+1] != t[i]) j = next[j];

		if (p[j+1] == t[i]) ++j;

		if (j >= 0) ++cnt[j];

		if (p[j+1] == '\0') j = next[j];
	}
}

char s[NN], t[NN];
int next[NN];
long long left[NN], right[NN];

int main()
{
	int nCase, lt;
	long long ans;

	scanf("%d", &nCase);
	while (nCase--) {
		ans = 0;
		scanf("%s", s);
		scanf("%s", t);
		
		for (lt = 0; t[lt]; ++lt) {
			left[lt] = right[lt] = 0;
		}

		make_next(t, next);
		kmp_count(s, t, next, left); 

		for (int i = lt - 1; i >= 0; --i) {
			if (next[i] >= 0) {
				left[next[i]] += left[i];
			}
		}

		strrev(s);
		strrev(t);
		make_next(t, next);
		kmp_count(s, t, next, right); 

		for (int i = lt - 1; i >= 0; --i) {
			if (next[i] >= 0) {
				right[next[i]] += right[i];
			}
		}

		ans = 0;
		for (int i = 1; i < lt; ++i) {
			ans += left[i-1] * right[lt - i - 1];
		}
		printf("%lld\n", ans);
	}
	return 0;
}

