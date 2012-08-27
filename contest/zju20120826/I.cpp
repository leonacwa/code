/* Information Sharing
 * 模拟题，使用STL的set
 * */
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

set<int> *pset[MAXN], mset[MAXN];

int fa[MAXN];
void init_fa() {
	for (int i = 0; i < MAXN; ++i) fa[i] = i;
}
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fy] = fx;
	}
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		map<string, int> ma;
		init_fa();
		char cmd[64], name[64], name2[64];
		int cnt = 0, ns;
		for (int i = 0; i < n; ++i) {
			scanf("%s", cmd);
			if (cmd[0] == 'a') {
				scanf("%s%d", name, &ns);
				int p = ma[name];
				if (p == 0) {
					p = ma[name] = ++cnt;
					pset[p] = mset + p;
					pset[p]->clear();
				}
				for (int i = 0, t; i < ns; ++i) {
					scanf("%d", &t);
					pset[p]->insert(t);
				}
			} else if (cmd[0] == 's') {
				scanf("%s%s", name, name2);
				int p1 = find(ma[name]), p2 = find(ma[name2]);
				if (p1 != p2) {
					if (pset[p1]->size() < pset[p2]->size()) {
						swap(pset[p1], pset[p2]);
					}
					for (set<int>::iterator it = pset[p2]->begin(); it != pset[p2]->end(); ++it) {
						pset[p1]->insert(*it);
					}
					join(p1, p2);
				}
			} else if (cmd[0] == 'c') {
				scanf("%s", name);
				int p = find(ma[name]);
				printf("%d\n", pset[p]->size());
			}
		}
	}
	return 0;
}
