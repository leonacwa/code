#include <cstdio>
#include <iostream>
using namespace std;

int f[2005][2005] = {0};
char s[2005];
int n, ls;
int del[26], add[26];

int main()
{
	while (EOF != scanf("%d %d", &n, &ls)) {
		scanf("%s", s);
		for (int i = 0; i < n; ++i) {
			char ch[3];
			int vd, va;
			scanf("%s %d %d", &ch, &va, &vd);
			add[ch[0] - 'a'] = va;
			del[ch[0] - 'a'] = vd;
		}
		for (int k = 1; k < ls; ++k) {
			for (int i = 0; i+k < ls; ++i) {
				int j = i + k;
				int t = min(f[i][j-1] + del[s[j] - 'a'], f[i][j-1] + add[s[j] - 'a']);
				t = min(t, min(f[i+1][j] + del[s[i] - 'a'], f[i+1][j] + add[s[i] - 'a']));
				if (s[i] == s[j]) {
					t = min(t, f[i+1][j-1]);
				} else {
					t = min(t, f[i+1][j-1] + del[s[i] - 'a'] + del[s[j] - 'a']);
					if (del[s[i] - 'a'] + add[s[j] - 'a'] < del[s[j] - 'a'] + add[s[i] - 'a']) {
						t = min(t, f[i+1][j-1] + del[s[i] - 'a'] + add[s[j] - 'a']);
					} else {
						t = min(t, f[i+1][j-1] + del[s[j] - 'a'] + add[s[i] - 'a']);
					}
				}
				f[i][j] = t;
			}
		}
		printf("%d\n", f[0][ls-1]);
	}
	return 0;
}

