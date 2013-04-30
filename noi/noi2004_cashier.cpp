/*
 * NOI 2004 郁闷的出纳员
 * */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

const int MAXN = 100005;

struct TreapNode {
	TreapNode *ch[2];
	int sz, fix;
	int val;
};

struct Treap {
#define LSZ(x) ((x).ch[0] ? (x).ch[0]->sz : 0)
#define RSZ(x) ((x).ch[1] ? (x).ch[1]->sz : 0)
	int del_cnt, delta;
	int mcnt, pcnt;
	TreapNode *root, mem[MAXN], *pool[MAXN];

	TreapNode *new_node(int val) {
		TreapNode* x;
		if (pcnt >= 0) x = pool[pcnt--];
		else x = mem + mcnt++;
		x->ch[0] = x->ch[1] = NULL;
		x->sz = 1;
		x->fix = rand();
		x->val = val;
		return x;
	}

	void rotate(TreapNode* &x, int c) {
		TreapNode *y = x->ch[!c];
		x->ch[!c] = y->ch[c];
		y->ch[c] = x;
		x = y;
		y = x->ch[c];
		y->sz = LSZ(*y) + RSZ(*y) + 1;
		x->sz = LSZ(*x) + RSZ(*x) + 1;
	}

	void insert(TreapNode* &x, int val) {
		if (x == NULL) {
			x = new_node(val);
		} else {
			int c = x->val < val;
			insert(x->ch[c], val);
			x->sz++;
			if (x->fix > x->ch[c]->fix) rotate(x, !c);
			x->sz = LSZ(*x) + RSZ(*x) + 1;
		}
	}

	void insert(int val) {
		insert(root, val - delta);
	}

	void del_low(TreapNode* &x, int val) {
		if (x == NULL) return;
		del_low(x->ch[0], val);
		x->sz = LSZ(*x) + RSZ(*x) + 1;
		if (x->val < val) {
			del_low(x->ch[1], val);
			pool[++pcnt] = x;
			x = x->ch[1];
			del_cnt++;
		}
		if (x) {
			if (x->ch[1] && x->fix > x->ch[1]->fix) {
				rotate(x, 0);
			}
			x->sz = LSZ(*x) + RSZ(*x) + 1;
		}
	}
	void del_low(int val) {
		del_low(root, val - delta);
	}

	TreapNode * find_kth(TreapNode*x, int k) {
		if (x == NULL) return NULL;
		int lsz = LSZ(*x);
		if (k <= lsz) {
			return find_kth(x->ch[0], k);
		} else if (k == lsz + 1) {
			return x;
		} else {
			return find_kth(x->ch[1], k - lsz - 1);
		}
	}
	int find_kth(int k) {
		if (k < 1 || k > size()) return -1;
		TreapNode *x = find_kth(root, k);
		if (x) return x->val + delta;
		return -1;
	}

	int size() {
		if (root) return root->sz;
		return 0;
	}
	void init() {
		mcnt = 0;
		pcnt = -1;
		root = NULL;
		del_cnt = 0;
		delta = 0;
	}
};

Treap tr;

int main() {
	int n, low;
	srand(time(0));
	while (EOF != scanf("%d%d", &n, &low)) {
		int k;
		char s[4];
		tr.init();
		while (n--) {
			scanf("%s%d", s, &k);
			if (s[0] == 'I') {
				if (k >= low) {
					tr.insert(k);
				} else {
	//				tr.del_cnt++;
	//				傻逼了，公司都没进，哪来的出公司啊
				}
			} else if (s[0] == 'A') {
				tr.delta += k;
			} else if (s[0] == 'S') {
				tr.delta -= k;
				tr.del_low(low);
			} else if (s[0] == 'F') {
				printf("%d\n", tr.find_kth(tr.size() - k + 1));
			} else {
				for(;;);
			}
		}
		printf("%d\n", tr.del_cnt);
	}
	return 0;
}
