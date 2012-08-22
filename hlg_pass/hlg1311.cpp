#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

struct Str {
	char s[11];
	bool operator < (const Str &b) const {
		return strcmp(s, b.s) < 0;
	}
};

int fa[1005];
int n;
int ID;
bool flag[1005];

int find(int x)
{
	if (x != fa[x]) fa[x] = find(fa[x]);
	return fa[x];
}

void union_set(int a, int b)
{
	int af = find(a), bf = find(b);
	if (af != bf) {
		fa[bf] = af;
	}
}

int main()
{
	Str s[3];
	while (EOF != scanf("%d", &n)) {
		map<Str, int> ma;
		ID = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s %s %s", s[0].s, s[1].s, s[2].s);
			int a = ma[s[0]];
			if (a == 0) {
				ma[s[0]] = a = ++ID;
				fa[a] = a;
			}
			int b = ma[s[1]];
			if (b == 0) {
				ma[s[1]] = b = ++ID;
				fa[b] = b;
			}
			int c = ma[s[2]];
			if (c == 0) {
				ma[s[2]] = c = ++ID;
				fa[c] = c;
			}
			union_set(a, b);
			union_set(a, c);
		}
		memset(flag, 0, sizeof(flag));
		int ans = 0;
		for (int i = 1; i <= ID; ++i) {
			int a = find(i);
			if (!flag[a]) {
				flag[a] = true;
				++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

