// T's time
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct Word {
	char s[32];
	int ls, fg;
};
int n, m;
Word word[32];
int minlen;
char T[1000];

int FG(char *s, int l, int r)
{
	int ret = 0;
	while (l <= r) {
		ret += s[l] - 'A';
		++l;
	}
	ret %= (minlen + 44);
	return ret; 
}

int main()
{
	int nCase = 0;
	while (EOF != scanf("%d %d", &n, &m)) {
		minlen = 1000000;
		for (int i = 0; i < n; ++i) {
			scanf("%s", word[i].s);
			word[i].ls = strlen(word[i].s);
			if (minlen > word[i].ls) {
				minlen = word[i].ls;
			}
		}
		scanf("%s", T);
		for (int i = 0; i < n; ++i) {
			word[i].fg = FG(word[i].s, word[i].ls - m, word[i].ls-1);
		}
		int lt = strlen(T);
		int i = 0;
		int ans = 0;
		while (i + m <= lt) {
			int sv = FG(T, i, i + m - 1);
			bool equal = false;
			for (int j = 0; j < n; ++j) {
				if (word[j].fg == sv) {
					equal = true;
					break;
				}
			}
			if (equal) {
				++ans;
				i += m + 1;
			} else {
				int skip = sv % 3;
				i += m + skip;
			}
		}
		printf("Scenario #%d\n%d\n\n", ++nCase, ans);
	}
	return 0;
}

