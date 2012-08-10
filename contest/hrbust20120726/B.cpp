#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

int g[205][205];
int d[205], Q[205];

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		memset(g, 0, sizeof(g));
		map<char, int> ma;
		char s[256];
		int id = 0;
		ma['w'] = ++id;
		int u, v;
		u = ma['s'] = ++id;
		v = ma['f'] = ++id;
		g[u][v] = 1;
		for (int i = 0; i < n; ++i) {
			scanf("%s", s);
			int ls = strlen(s);
			u = ma[s[0]], v = ma[s[ls-1]];
			if (u == 0) u = ma[s[0]] = ++id;
			if (v == 0) v = ma[s[ls-1]] = ++id;
			g[u][v] = 1;
		}
		for (int i = 0; i <= id; ++i) d[i] = id;
		int *fr = Q, *ta = Q;
		int self = ma['s'];
		d[self] = 0;
		*ta++ = self;
		while (fr < ta) {
			u = *fr++;
			for (int i = 1; i <= id; ++i) {
				if (d[i] == id && g[u][i]) {
					d[i] = d[u] + 1;
					*ta++ = i;
				}
			}
		}
		int wing = ma['w'];
		if (d[wing] < id) puts("Yes");
		else puts("No");
	}
	return 0;
}

