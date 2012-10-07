/* NOI2005 维护数列
 * SplayTree题，调得我吐血
 * 其实还是push_up push_down没写好，有些信息用懒惰更新，还得在push_up的时候去更新一下
 * 可以做模板用
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 4000000 + 6;
struct SplayTree {
	struct Node {
		Node *ch[2], *pre;
		int sz;
		int val, sum;
		bool rev, same;
		int mmax, lmax, rmax;
	};
#define keyTree (root->ch[1]->ch[0])
	Node *root, *null_node;
	Node mem[MAXN];
	Node *que[MAXN], *pool[MAXN];
	int mem_cnt, top;

	void push_up(Node *x) {
		if (x == null_node) return;
		x->sz = 1;
		x->sum = x->lmax = x->rmax = x->val;
		int mmax = x->val;
		if (x->ch[0] != null_node) {
			push_down(x->ch[0]); /* 有可能还没更新完成 */
			x->lmax = max(x->ch[0]->lmax, x->ch[0]->sum + x->lmax);
			x->rmax = max(x->val, x->ch[0]->rmax + x->val);
			mmax = max(mmax, max(x->ch[0]->mmax, max(x->lmax, max(x->rmax, x->ch[0]->rmax+x->val))));
			x->sz += x->ch[0]->sz;
			x->sum += x->ch[0]->sum;
		}
		if (x->ch[1] != null_node) {
			push_down(x->ch[1]); /* 有可能还没更新完成 */
			x->lmax = max(x->lmax, x->sum + x->ch[1]->lmax);
			x->rmax = max(x->ch[1]->rmax, x->rmax + x->ch[1]->sum);
			mmax = max(mmax, max(x->ch[1]->mmax, max(x->lmax, x->rmax)));
			mmax = max(mmax, max(0, (x->ch[0]==null_node)?0:x->ch[0]->rmax)+x->val+x->ch[1]->lmax);
			x->sz += x->ch[1]->sz;
			x->sum += x->ch[1]->sum;
		}
		x->mmax = mmax;
	}
	void push_down(Node *x) {
		if (x == null_node) return;
		if (x->same) {
			x->same = 0;
			x->sum = x->val * x->sz;
			if (x->val > 0) {
				x->mmax = x->lmax = x->rmax = x->sum;
			} else {
				x->mmax = x->lmax = x->rmax = x->val;
			}
			x->ch[0]->same = x->ch[1]->same = 1;
			x->ch[0]->val = x->ch[1]->val = x->val;
		}
		if (x->rev) {
			x->rev = 0;
			swap(x->ch[0], x->ch[1]);
			swap(x->lmax, x->rmax);
			x->ch[0]->rev ^= 1;
			x->ch[1]->rev ^= 1;
		}
	}
	/** 旋转操作，c=0表示左旋，逆时针，c=1表示右旋，顺时针 */
	void rotate(Node *x, int c) {
		Node *y = x->pre;
		push_down(y);
		push_down(x);
		y->ch[!c] = x->ch[c];
		if (x->ch[c] != null_node) x->ch[c]->pre = y;
		x->pre = y->pre;
		if (y->pre != null_node) y->pre->ch[ y == y->pre->ch[1] ] = x; 
		x->ch[c] = y;
		y->pre = x;
		push_up(y);
	}
	/** 伸展的操作，将x节点转到f下，f要在x之上，f为null_node时表示x转为根 */
	void splay(Node *x, Node *f) {
		push_down(x);
		while (x->pre != f) {
			if (x->pre->pre == f) {
				rotate(x, x->pre->ch[0] == x);
			} else {
				Node *y = x->pre, *z = y->pre;
				bool c = (z->ch[0] == y);
				if (y->ch[c] == x) {
					rotate(x, !c);
					rotate(x, c);
				} else {
					rotate(y, c);
					rotate(x, c);
				}
			}
		}
		push_up(x);
		if (f == null_node) root = x;
	}
	bool select(int k, Node *f) {
		Node *x = root;
		for (;;) {
			push_down(x); /* 需要先推下去，有可能这个区间会翻转，这样就不会弄错左右子树的节点数了*/
			int sz = x->ch[0]->sz;
			if (sz + 1 == k) break;
			if (k <= sz) {
				x = x->ch[0];
			} else {
				k -= sz + 1;
				x = x->ch[1];
			}
			if (x == null_node) {
				return false;
			}
		}
		splay(x, f);
		return true;
	}
	int size() const {
		return root->sz - 2;
	}
	Node* new_node(int val) {
		Node *x;
		if (top >= 0) x = pool[top--];
		else x = mem + mem_cnt++;
		x->pre = x->ch[0] = x->ch[1] = null_node;
		x->sz = 1;
		x->val = x->sum = x->mmax = x->lmax = x->rmax = val;
		x->rev  = x->same = 0;
		return x;
	}
	void make_tree(Node *&x, Node *f, int a[], int tot) {
		if (tot <= 0) return;
		int m = (tot - 1) >> 1;
		x = new_node(a[m]);
		x->pre = f;
		make_tree(x->ch[0], x, a, m);
		make_tree(x->ch[1], x, a+m+1, tot-m-1);
		push_up(x);
	}
	void init(int n, int a[]) {
		null_node = mem;
		memset(null_node, 0, sizeof(Node));
		null_node->pre = null_node->ch[0] = null_node->ch[1] = null_node;
		mem_cnt = 1, top = -1;

		// 开头和末尾添加两个节点，避免特判，方便取区间，但是节点数变为n+2
		root = new_node(-1);
		root->ch[1] = new_node(-1);
		root->ch[1]->pre = root;
		root->sz = 2; /* 可能要用push_up */

		make_tree(keyTree, root->ch[1], a, n);
		push_up(root->ch[1]);
		push_up(root);
	}
	/* 将 [l,r] 区间转到 keyTree */
	void ch_key_tree(int l, int r) {
		select(l, null_node);
		select(r+2, root);
	}
	void insert(int pos, int a[], int n) {
		Node *tmp_root = root, *tmp_root2;

		make_tree(root, null_node, a, n);
		tmp_root2 = root;
		root = tmp_root;

		ch_key_tree(pos+1, pos);

		keyTree = tmp_root2;
		keyTree->pre = root->ch[1]; /* 忘记维护pre，导致调了一天 */

		push_up(root->ch[1]);
		push_up(root);
	}
	void erase(Node * &x) {
		if (x == null_node) {
			return;
		}
		Node *f = x->pre, **fr = que, **ta = que;
		*ta++ = x;
		while (fr < ta) {
			x = *fr++;
			pool[++top] = x;
			if (x->ch[0] != null_node) *ta++ = x->ch[0];
			if (x->ch[1] != null_node) *ta++ = x->ch[1];
		}
		x = null_node;
		if (f != null_node) push_up(f);
	}
	void pre_ord(Node *x) {
		if (x == null_node) return;
		for (int i = 0; i < 2; ++i)
			if (x->ch[i] != null_node && x->ch[i]->pre != x) {
				printf("error pre %d(%p)<-%d(%p)\n", x->val, x, x->ch[i]->val, x->ch[0]);
			}
		if (x->sz != 1 + x->ch[0]->sz + x->ch[1]->sz) {
			printf("error sz %d:%d  %p %d\n", x->sz, 1+x->ch[0]->sz+x->ch[1]->sz, x, x->val);
		}
		if (x->ch[0]) pre_ord(x->ch[0]);
		printf("%d ", x->val);
		//printf("%d(%p)  ", x->val, x);
		if (x->ch[1]) pre_ord(x->ch[1]);
	}
	void travel() {
		pre_ord(root);
		printf("\n");
	}
	void del(int pos, int tot) {
		ch_key_tree(pos, pos+tot-1);
		erase(keyTree);
		push_up(root);
	}
	void make_same(int pos, int tot, int val) {
		ch_key_tree(pos, pos+tot-1);
		keyTree->same = 1;
		keyTree->val = val;
	}
	void reverse(int pos, int tot) {
		ch_key_tree(pos, pos+tot-1);
		keyTree->rev ^= 1;
	}
	int get_sum(int pos, int tot) {
		ch_key_tree(pos, pos+tot-1);
		push_down(keyTree);
		return keyTree->sum;
	}
	int max_sum() {
		ch_key_tree(1, size());
		push_down(keyTree);
		return keyTree->mmax;
	}
};

SplayTree spt;
int a[MAXN];

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		spt.init(n, a);
		while (m--) {
			int pos, tot;
			char cmd[65];
			scanf("%s", cmd);
			//	printf("%s\n", cmd);
			if (0 == strcmp(cmd, "INSERT")) {
				scanf("%d%d", &pos, &tot);
				for (int i = 0; i < tot; ++i) scanf("%d", &a[i]);
				spt.insert(pos, a, tot);
			} else if (0 == strcmp(cmd, "DELETE")) {
				scanf("%d%d", &pos, &tot);
				spt.del(pos, tot);
			} else if (0 == strcmp(cmd, "MAKE-SAME")) {
				int c;
				scanf("%d%d%d", &pos, &tot, &c);
				spt.make_same(pos, tot, c);
			} else if (0 == strcmp(cmd, "REVERSE")) {
				scanf("%d%d", &pos, &tot);
				spt.reverse(pos, tot);
			} else if (0 == strcmp(cmd, "GET-SUM")) {
				scanf("%d%d", &pos, &tot);
				printf("%d\n", spt.get_sum(pos, tot));
			} else if (0 == strcmp(cmd, "MAX-SUM")) {
				printf("%d\n", spt.max_sum());
			} else {
				printf("error cmd:%s\n", cmd);
			}
		}
	}
	return 0;
}
