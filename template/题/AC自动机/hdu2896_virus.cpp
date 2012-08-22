/* AC自动机入门题
 * 模板题`
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 500 * 201 + 100;
const int MAX_CHILD = 128;

struct Node {
	int id;
	Node *son[MAX_CHILD], *fail;
} nd[MAXN];
int nd_cnt;

Node* newNode()
{
	Node *p = nd + nd_cnt++;
	memset(p, 0, sizeof(Node));
	return p;
}

void insert(Node *root, const char *s, int id)
{
	Node * p = root;
	for (; *s; ++s) {
		if (p->son[*s] == NULL) {
			p->son[*s] = newNode();
		}
		p = p->son[*s];
	}
	p->id = id;
}

void AC_construct(Node *root)
{
	Node *p = root;
	queue<Node*> Q;
	for (int i = 0; i < MAX_CHILD; ++i) {
		if (p->son[i]) {
			p->son[i]->fail = root;
			Q.push(p->son[i]);
		} else {
			p->son[i] = root;
		}
	}
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		for (int i = 0; i < MAX_CHILD; ++i) {
			if (p->son[i]) {
				Q.push(p->son[i]);
				Node *v = p->fail;
				while (v->son[i] == NULL) v = v->fail;
				p->son[i]->fail = v->son[i];
			} else {
				p->son[i] = p->fail->son[i];
			}
		}
	}
}

int AC_find(Node *root, const char *s, bool vis[])
{
	int ret = 0;
	Node *p = root, *q;
	for (; *s; ++s) {
		while (p->son[*s] == NULL) p = p->fail;
		q = p = p->son[*s];
		while (q != root && q->id != -1) {
			if (q->id > 0) ret++;
			vis[q->id] = true;
			q = q->fail;
		}
	}
	return ret;
}

char virus[256], src[10000 + 100];
bool vis[1005];

int main()
{
	int n, m;
	while (EOF != scanf("%d", &n)) {
		nd_cnt = 0;
		Node *root = newNode();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", virus);
			insert(root, virus, i);
		}
		AC_construct(root);
		scanf("%d", &m);
		int ans = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%s", src);
			memset(vis, 0, sizeof(vis));
			int ret = AC_find(root, src, vis);
			if (ret > 0) {
				++ans;
				printf("web %d:", i);
				for (int j = 1; j <= n; ++j) {
					if (vis[j])	printf(" %d", j);
				}
				puts("");
			}
		}
		printf("total: %d\n", ans);
	}
	return 0;
}

