/*
 * spoj SUBLEX
 * http://www.spoj.pl/problems/SUBLEX/
 * 这题用的评测机太老了，需要在常数优化
 **/
#include <cstdio>
#include <cstring>

const int MAXN = 90001;

struct SuffixAutomaton {
	struct Node {
		int len, cnt;
		Node *f, *ch[26];
		char c;
	};
	Node *root, *last;
	Node pool[MAXN*2];
	int cnt;

	void init() {
		root = last = pool;
		//memset(root, 0, sizeof(Node));
		cnt = 1;
	}

	void append(char ch) {
		int c = ch - 'a';
		Node *p = last, *np = pool + cnt++;
		//memset(np, 0, sizeof(Node));
		np->len = last->len + 1, np->cnt = 1;
		last = np;
		for (; p && !p->ch[c]; p = p->f) p->ch[c] = np;
		if (!p) {
			np->f = root;
		} else {
			if (p->ch[c]->len == p->len+1) {
				np->f = p->ch[c];
			} else {
				Node *q = p->ch[c], *nq = pool + cnt++;
				memcpy(nq, q, sizeof(Node));
				nq->len = p->len + 1;
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
	gets(str);
	sam.init();
	int ls = 0;
	for (; str[ls]; ++ls) sam.append(str[ls]);
	for (int i = 0; i < sam.cnt; ++i) ++buc[ sam.pool[i].len ];
	for (int i = 1; i <= ls; ++i) buc[i] += buc[i-1];
	for (int i = 0; i < sam.cnt; ++i) sorted[ --buc[ sam.pool[i].len ] ] = sam.pool + i;
	for (int i = sam.cnt-1; i >= 0; --i) {
		int k = 0;
		SuffixAutomaton::Node *p = sorted[i];
		for (int c = 0; c < 26; ++c) {
			if (p->ch[c]) {
				p->cnt += p->ch[c]->cnt;
				p->ch[c]->c = 'a' + c;
				p->ch[k++] = p->ch[c];
			}
		}
		p->ch[k] = NULL;
	}
	int m, k;
	scanf("%d", &m);
	while (m--) {
		scanf("%d", &k);
		SuffixAutomaton::Node *p = sam.root, *q;
		int l = 0;
		while (k) {
			for (int i = 0; p->ch[i]; ++i) {
				q = p->ch[i];
				if (q->cnt < k) {
					k -= q->cnt;
				} else {
					str[l++] = q->c;
					p = q;
					--k;
					break;
				}
			}
		}
		str[l] = '\0';
		puts(str);
	}
	return 0;
}
