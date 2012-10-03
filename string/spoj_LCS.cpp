/*
   spoj LCS
http://www.spoj.pl/problems/LCS/
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 250005;
struct SuffixAutomaton {
	struct Node {
		int len;
		Node *f, *ch[26];
		Node() {}
		Node(int l) : len(l), f(NULL) {
			memset(ch, 0, sizeof(ch));
		}
	};
	Node *root, *last;
	Node pool[MAXN*2];
	int cnt;

	void init() {
		root = last = pool;
		memset(root, 0, sizeof(Node));
		cnt = 1;
	}
	Node* new_node(int l = 0) {
		Node *x = pool + cnt++;
		memset(x, 0, sizeof(Node));
		if (l != 0) x->len = l;
		return x;
	}
	void append(char ch) {
		int c = ch - 'a';
		Node *p = last, *np = new_node(last->len+1);
		last = np;
		for (; NULL != p && NULL == p->ch[c]; p = p->f) p->ch[c] = np;
		if (NULL == p) {
			np->f = root;
		} else {
			if (p->ch[c]->len == p->len+1) {
				np->f = p->ch[c];
			} else {
				Node *q = p->ch[c], *nq = new_node();
				*nq = *q;
				nq->len = p->len + 1;
				q->f = np->f = nq;
				for (; NULL != p && p->ch[c] == q; p = p->f) p->ch[c] = nq;
			}
		}
	}
};
SuffixAutomaton sam;
char str[MAXN];

int main() {
	while (EOF != scanf("%s", str)) {
		sam.init();
		for (int i = 0; str[i]; ++i) sam.append(str[i]);
		scanf("%s", str);
		int ans = 0, nl = 0;
		SuffixAutomaton::Node *p = sam.root;
		for (int i = 0; str[i]; ++i) {
			int c = str[i] - 'a';
			if (p->ch[c] != NULL) {
				p = p->ch[c];
				++nl;
			} else {
				for (; NULL != p && NULL == p->ch[c]; p = p->f) ;
				if (p == NULL) {
					nl = 0;
					p = sam.root;
				} else {
					nl = p->len + 1;
					p = p->ch[c];
				}
			}
			ans < nl ? ans = nl : 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
