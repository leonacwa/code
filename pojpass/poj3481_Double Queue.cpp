/*
 * POJ 3481 Double Queue
 * Treap树解
 * */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1000006;

struct TreapNode {
	TreapNode *ch[2];
	int sz, fix;
	int lsz() { return ch[0] ? ch[0]->sz : 0; }
	int rsz() { return ch[1] ? ch[1]->sz : 0; }
	int val, id;
};
struct Treap {
	int mcnt, pcnt;
	TreapNode *root, mem[MAXN], *pool[MAXN];

	void init() {
		mcnt = 0;
		pcnt = -1;
		root = NULL;
	}

	TreapNode * new_node(int val, int id) {
		TreapNode* x;
		if (pcnt >= 0) x = pool[pcnt--];
		else x = mem + mcnt++;
		x->ch[0] = x->ch[1] = NULL;
		x->sz = 1;
		x->fix = rand();
		x->val = val;
		x->id = id;
		return x;
	}

	void rotate(TreapNode* &x, int c) {
		TreapNode* y = x->ch[!c];
		x->ch[!c] = y->ch[c];
		y->ch[c] = x;
		x = y;
		y = x->ch[c];
		y->sz = y->lsz() + y->rsz() + 1;
		x->sz = x->lsz() + x->rsz() + 1;
	}

	void insert(TreapNode* &x, int val, int id) {
		if (x == NULL) {
			x = new_node(val, id);
		} else {
			int c = x->val < val;
			insert(x->ch[c], val, id);
			x->sz++;
			if (x->fix > x->ch[c]->fix) rotate(x, !c);
		}
	}
	void insert(int val, int id) {
		insert(root, val, id);
	}

	PII del_max(TreapNode * &x) {
		PII ii;
		if (NULL == x->ch[1]) {
			ii = make_pair(x->val, x->id);
			pool[++pcnt] = x;
			if (x->ch[0]) x = x->ch[0];
			else x = NULL;
		} else {
			ii = del_max(x->ch[1]);
			x->sz--;
		}
		return ii;
	}
	PII del_max() {
		if (root) return del_max(root);
		else return make_pair(0, 0);
	}
	PII del_min(TreapNode * &x) {
		PII ii;
		if (NULL == x->ch[0]) {
			ii = make_pair(x->val, x->id);
			pool[++pcnt] = x;
			if (x->ch[1]) x = x->ch[1];
			else x = NULL;
		} else {
			ii = del_min(x->ch[0]);
			x->sz--;
		}
		return ii;
	}
	PII del_min() {
		if (root) return del_min(root);
		else return make_pair(0, 0);
	}

};
Treap tr;

int main() {
	int cmd;
	tr.init();
	while (EOF != scanf("%d", &cmd)) {
		if (cmd == 0) {
			tr.init();
			continue;
		}
		if (cmd == 1) {
			int k, p;
			scanf("%d%d", &k, &p);
			tr.insert(p, k);
		} else if (cmd == 2) {
			PII ii = tr.del_max();
		//	printf("hig %d\n", ii.first);
			printf("%d\n", ii.second);
		} else if (cmd == 3) {
			PII ii = tr.del_min();
	//		printf("low %d\n", ii.first);
			printf("%d\n", ii.second);
		} else {
		}
	}
	return 0;
}
