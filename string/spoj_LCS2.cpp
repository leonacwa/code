/*
 * spoj LCS2
 * http://www.spoj.pl/problems/LCS2/
 * from:http://hi.baidu.com/wyl8899/item/fe30282b5f7c4dd50f37f96d
 * 对于每个节点，维护两个量：f(s)为正在跑的串在s状态的最大匹配长度，g(s)为此前的所有f(s)与Max(s)的最小值。
 * 需要注意的是，可能走到了某个状态s却没有走到pre(s)，因此f(s)被更新了而f(pre(s))没有，然而显然f(pre(s))也应被更新。
 * 因此，每跑完一个串了以后，按照pre关系更新一遍所有的f(s)，然后再用f(s)去更新g(s)。
 * 最后在g(s)中取最大值即可。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

struct SuffixAutomaton {
	struct Node {
		int len;
		Node *f, *ch[26];
		int nl, ml;
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
		if (l) x->len = x->ml = l;
		return x;
	}
	void append(char ch) {
		int c = ch - 'a';
		Node *p = last, *np = new_node(last->len + 1);
		last = np;
		for (; p && !p->ch[c]; p = p->f) p->ch[c] = np;
		if (!p) {
			np->f = root;
		} else {
			if (p->ch[c]->len == p->len+1) {
				np->f = p->ch[c];
			} else {
				Node *q = p->ch[c], *nq = new_node();
				*nq = *q;
				nq->len = nq->ml = p->len + 1;
				q->f = np->f = nq;
				for (; p && p->ch[c] == q; p = p->f) p->ch[c] = nq;
			}
		}
	}
};
SuffixAutomaton sam;
char str[MAXN];
int buc[MAXN];
SuffixAutomaton::Node* sorted[MAXN*2];

int main() {
	scanf("%s", str);
	sam.init();
	int ls = 0;
	for (; str[ls]; ++ls) sam.append(str[ls]);
	for (int i = 0; i < sam.cnt; ++i) ++buc[ sam.pool[i].len ];
	for (int i = 1; i <= ls; ++i) buc[i] += buc[i-1];
	for (int i = 0; i < sam.cnt; ++i) sorted[ --buc[ sam.pool[i].len ] ] = sam.pool + i;
	while (EOF != scanf("%s", str)) {
		SuffixAutomaton::Node *p = sam.root;
		int nl = 0;
		for (int i = 0; str[i]; ++i) {
			int c = str[i] - 'a';
			if (p->ch[c]) {
				p = p->ch[c];
				++nl;
				if (p->nl < nl) p->nl = nl;
			} else {
				for (; p && !p->ch[c]; p = p->f) ;
				if (p) {
					nl = p->len + 1;
					p = p->ch[c];
					if (p->nl < nl) p->nl = nl;
				} else {
					p = sam.root;
					nl = 0;
				}
			}
		}
		for (int i = sam.cnt-1; i >= 0; --i) {
			SuffixAutomaton::Node *q = sorted[i];
			if (q->ml > q->nl) q->ml = q->nl;
			if (q->f && q->f->nl < q->nl) q->f->nl = q->nl; /* 后缀树的特点所决定,q->f表示的后缀是q的真子集,那么q能有的答案，自然就能被q->f所包含*/
			q->nl = 0;
		}
	}
	int ans = 0;
	for (int i = 0; i < sam.cnt; ++i) {
		if (ans < sam.pool[i].ml) ans = sam.pool[i].ml;
	}
	printf("%d\n", ans);
	return 0;
}
