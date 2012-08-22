/* KMP
 * 时间复杂度 O(n+m)
 * */
#include <stdio.h>
#define MAXN 100000

char s[MAXN];
int next[MAXN];

/* next[i]表示i的前一个匹配位置，
 * 也表示模式串T的 T[0..next[i]] == T[(i - next[i])..i]，next[i]==-1时不存在该关系
 * 也就是说,next[i]+1是以第i-next[i]开头的字符串跟T的最长前缀长度
 * */

int make_next(char s[], int next[])
{
	int i,  k = -1;
	next[0] = -1;
	for (i = 1; s[i]; i++) {
		while (k >= 0 && s[k+1] != s[i]) k = next[k];
		if (s[k+1] == s[i]) k++;
		next[i] = k;
	}
	return i;
}

char* kmp_strstr(char s[], char t[])
{
	int k = -1;
	int nl = make_next(t, next);
	for (int i = 0; s[i] != '\0'; i++) {
		while (k >= 0 && s[i] != t[k+1]) k = next[k];
		if (s[i] == t[k+1]) k++;
		if (t[k+1] == '\0') return &s[i-k];
	}
	return NULL;
}

int main()
{
	char s[] = "Search Internet VagaaVagaa!";
	char t[] = "VagaaVagaa";
	char* ptr;
	printf("%s %s\n", s, t);
	ptr = kmp_strstr(s, t);
	for (int i = 0; t[i]; i++) {
		printf("%d ", next[i]);
	}
	printf("\n");
	puts(ptr);
	return 0;
}

