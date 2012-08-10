#include <stdio.h>

const int NN= 100000 + 5;

char s[NN], t[NN];
int next[2][NN];

int make_next(char s[], int next[])
{
	int i,  k = -1;
	next[0] = -1;
	for (i = 1; s[i] != '\0'; i++) {
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

char* kmp_strstr(char s[], char t[], int next[])
{
	int k = -1;
	//int nl = make_next(t, next);
	for (int i = 0; s[i] != '\0'; i++) {
		while (k >= 0 && s[i] != t[k+1]) {
			k = next[k];
		}
		if (s[i] == t[k+1]) {
			k++;
		}
		if (t[k+1] == '\0') {
			return &s[i-k];
		}
	}
	return NULL;
}

int kmp_str_count(char s[], char t[], int next[])
{
	int k = -1, ret = 0;
	//int nl = make_next(t, next);
	for (int i = 0; s[i] != '\0'; i++) {
		while (k >= 0 && s[i] != t[k+1]) {
			k = next[k];
		}
		if (s[i] == t[k+1]) {
			k++;
		}
		if (t[k+1] == '\0') {
			++ret;
			k = -1;
		}
	}
	return ret;
}

int main()
{
	int nCase;
	char ch;
	long long a, b, ans;

	scanf("%d", &nCase);
	while (nCase--) {
		ans = 0;
		scanf("%s", s);
		scanf("%s", t);
		for (int i = 1; t[i]; ++i) {
			ch = t[i];
			t[i] = 0;
			make_next(t, next[0]);
			if (NULL == kmp_strstr(s, t, next[0])) continue;
			t[i] = ch;
			make_next(t+i, next[1]);
			if (NULL == kmp_strstr(s, t, next[1])) continue;
			
			ch = t[i];
			t[i] = 0;
			a = kmp_str_count(s, t, next[0]);
			t[i] = ch;
			b = kmp_str_count(s, t+1, next[1]);
			ans += a * b;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

