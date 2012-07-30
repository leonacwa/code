/* AC自动机
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 1000 * 51 + 100;
const int MAX_CHILD = 26;

struct Node {
	int id;
	Node *son[MAX_CHILD], *fail;
} nd[MAXN];
int nd_cnt;
int ch_num[128];

int cnt[1005];
char virus[1005][55];

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
		int i = ch_num[*s];
		if (i == -1) continue;
		if (p->son[i] == NULL) {
			p->son[i] = newNode();
		}
		p = p->son[i];
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

void AC_find(Node *root, const char *s)
{
	Node *p = root, *q;
	for (; *s; ++s) {
		int i = ch_num[*s];
		if (i == -1) {
			p = root;
			continue;
		}
		while (p->son[i] == NULL) p = p->fail;
		q = p = p->son[i];
		while (q != root && q->id != -1) {
			if (q->id > 0) cnt[q->id]++;
			q = q->fail;
		}
	}
}

char src[2000000 + 100];

int main()
{
	memset(ch_num, -1, sizeof(ch_num));
	for (int i = 0; i < 26; ++i) ch_num['A' + i] = i;
	int n;
	while (EOF != scanf("%d", &n)) {
		nd_cnt = 0;
		Node *root = newNode();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", virus[i]);
			cnt[i] = 0;
			insert(root, virus[i], i);
		}
		AC_construct(root);
		scanf("%s", src);
		AC_find(root, src);
		for (int i = 1; i <= n; ++i) {
			if (cnt[i] > 0) {
				printf("%s: %d\n", virus[i], cnt[i]);
			}
		}
	}
	return 0;
}

