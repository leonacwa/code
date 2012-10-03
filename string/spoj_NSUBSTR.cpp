/* spoj NSUBSTR 
 * 后缀自动机
 * */
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
		Node(int l) :len(l), f(NULL) {
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
	Node *new_node(int l = 0) {
		Node *ptr = pool + cnt++;
		memset(ptr, 0, sizeof(Node));
		if (l != 0) ptr->len = l;
		return ptr;
	}
	void append(char ch) {
		int c = ch - 'a';
		Node *p = last, *np = new_node(last->len+1);
		last = np;
		for (; p && NULL==p->ch[c]; p = p->f) p->ch[c] = np;
		if (p == NULL) {
			np->f = root;
		} else {
			if (p->ch[c]->len == p->len+1) {
				np->f = p->ch[c];
			} else {
				Node *q = p->ch[c], *nq = new_node();
				*nq = *q;
				nq->len = p->len + 1;
				q->f = np->f = nq;
				for (; p && p->ch[c] == q; p = p->f) p->ch[c] = nq;
			}
		}
	}
};

template <class T>
void check_max(T &a, const T &b) {
	if (a < b) a = b;
}

SuffixAutomaton sam;
char str[MAXN];
int buc[MAXN];
int sorted[MAXN*2];
int c[MAXN*2];
int F[MAXN];

int main() {
	while (EOF != scanf("%s", str)) {
		int ls = strlen(str);
		sam.init();
		for (int i = 0; str[i]; ++i) {
			sam.append(str[i]);
		}
		// 基数排序，求出拓扑序列,按照长度从短到长即可
		memset(buc, 0, sizeof(buc));
		for (int i = 0; i < sam.cnt; ++i) ++buc[sam.pool[i].len];
		for (int i = 1; i <= ls; ++i) buc[i] += buc[i-1];
		for (int i = 0; i < sam.cnt; ++i) sorted[ --buc[ sam.pool[i].len ] ] = i;

		SuffixAutomaton::Node *ptr = sam.root;
		c[0] = 0;
		for (int i = 0; i < ls; ++i) c[ (ptr=ptr->ch[str[i]-'a']) - sam.pool ] = 1; // 包含自身的算一个
		memset(F, 0, sizeof(F));
		for (int i = sam.cnt-1; i >= 0; --i) {
			check_max(F[ sam.pool[ sorted[i] ].len], c[ sorted[i] ]);
			// 从fail指针找到一个
			if (NULL != sam.pool[ sorted[i] ].f) c[sam.pool[ sorted[i] ].f - sam.pool] += c[ sorted[i] ];
		}
		// 下面这个for去掉也能过，说明是无用的，更说明我还没懂后缀自动机
		for (int i = ls - 1; i >= 0; --i) check_max(F[i], F[i+1]);
		for (int i = 1; i <= ls; ++i) printf("%d\n", F[i]);
	}
	return 0;
}
