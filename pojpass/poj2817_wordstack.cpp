#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int NN = 10;
int n;
char word[NN][11];
int same[NN][NN];
int f[1<<NN][NN];

int getSame(char *s1, char *s2)
{
	int a = 0;
	for (char *sa = s1; *sa; ++sa) {
		int b = 0;
		char *pa = sa, *pb = s2;
		while (*pa && *pb) {
			if (*pa++ == *pb++) ++b;
		}
		if (a < b) a = b;
	}
	return a;
}

int dp(int s, int k)
{
	if (f[s][k] != -1) return f[s][k];
	f[s][k] = 0;
	int st = s ^ (1 << k);
	//int st = s & (~(1 << k));
	for (int i = 0; i < n; ++i) {
		if (!(st & (1 << i))) continue;
		int ret = dp(st, i);
		if (f[s][k] < ret + same[i][k]) {
			f[s][k] = ret + same[i][k];
		}
	}
	return f[s][k];
}

int main()
{
	while (EOF != scanf("%d", &n) && n > 0) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", word[i]);
		}
		memset(same, 0, sizeof(same));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				same[i][j] = max(same[i][j], getSame(word[i], word[j]));
				same[j][i] = max(same[j][i], same[i][j]);
			}
		}
		int ans = 0;
		int s = (1 << n) - 1;
		memset(f, -1, sizeof(f)); 
		for (int i = 0; i < n; ++i) {
			int t = dp(s, i);
			if (ans < t) ans = t;
		}
		printf("%d\n", ans);
	}
		return 0;
	}

