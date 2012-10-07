const int MAXN = 250005;

struct SuffixAutomaton {
	struct Node {
		int len;
		Node *f, *ch[26];
	};
	Node *root, *last;
	Node pool[MAXN*2];
	int cnt;

	void init() {
		root = last = pool;
		memset(root, 0, sizeof(Node));
		cnt = 1;
	}
	void append(char ch) { /* 添加一个字符到末尾，last为一个后缀终止态，沿着last->f走，经过的都是终止态 */
		int c = ch - 'a';
		Node *p = last, *np = pool + cnt++;
		memset(np, 0, sizeof(Node));
		np->len = last->len + 1;
		last = np;
		for (; NULL != p && NULL == p->ch[c]; p = p->f) p->ch[c] = np;
		if (p == NULL) {
			np->f = root;
		} else {
			if (p->ch[c]->len == p->len+1) {
				np->f = p->ch[c];
			} else { /* 新建一个节点，避免接受不存在的后缀 */
				Node *q = p->ch[c], *nq = pool + cnt++;
				*nq = *q;
				nq->len = p->len + 1;
				q->f = np->f = nq;
				for (; NULL != p && p->ch[c] == q; p = p->f) p->ch[c] = nq;
			}
		}
	}
};

