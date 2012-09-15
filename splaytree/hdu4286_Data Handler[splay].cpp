/* HDU 4286 Data Handler
 * Splay 写法
 * */
#include <cstdio>
#include <cstring>
/* 杭电的Judge是windows下的，windows栈太小 */
#pragma comment(linker, "/STACK:102400000,102400000") 

const int MAXN = 1000006;

struct Node {
	Node *pre, *ch[2];
	int sz;
/* 题目需要 */
	bool rev;
	int val;
};

struct SplayTree {
#define keyTree (root->ch[1]->ch[0])
	Node *root, *null_s; // null_s作为特殊的空节点
	int m_cnt, top;
	Node mem[MAXN], *pool[MAXN], *que[MAXN];

	void pushDown(Node *x) {
		if (x == null_s) printf("null_s\n");
		if (x != null_s && x->rev) {
			Node *tx = x->ch[0];
			x->ch[0] = x->ch[1];
			x->ch[1] = tx;
			x->ch[0]->rev ^= 1;
			x->ch[1]->rev ^= 1;
			x->rev = 0;
		}
	}
	void pushUp(Node *x) {
		x->sz = 1 + x->ch[0]->sz + x->ch[1]->sz;
	}

	/* 旋转操作，c=0表示左旋，逆时针，c=1表示右旋，顺时针
	 * */
	void rotate(Node *x, int c) {
		Node *y = x->pre;
		pushDown(y);
		pushDown(x);
		y->ch[!c] = x->ch[c];
		if (x->ch[c]) x->ch[c]->pre = y;
		x->pre = y->pre;
		if (y->pre != NULL) y->pre->ch[ y->pre->ch[1] == y ] = x;
		x->ch[c] = y;
		y->pre = x;
		pushUp(y);
	}
	void splay(Node *x, Node *f) {
		pushDown(x);
		while (x->pre != f) {
			if (x->pre->pre == f) {
				rotate(x, x->pre->ch[0] == x);
			} else {
				Node *y = x->pre, *z = y->pre;
				int c = (z->ch[0] == y);
				if (y->ch[c] == x) { // 之形旋转
					rotate(x, !c);
					rotate(x, c);
				} else { // 一形旋转
					rotate(y, c);
					rotate(x, c);
				}
			}
		}
		pushUp(x);
		if (f == null_s) root = x;
	}
	bool select(int k, Node *f) {
		Node *x = root;
		for (;;) {
			pushDown(x); /* 需要先推下去，有可能这个区间会翻转，这样就不会弄错左右子树的节点数了*/
			int sz = x->ch[0]->sz;
			if (sz+1 == k) break;
			if (k <= sz) {
				x = x->ch[0];
			} else {
				k -= sz + 1;
				x = x->ch[1];
			}
			if (x == null_s) {
				printf("sel error null_s\n");
				return false;
			}
		}
		splay(x, f);
		return true;
	}
	int size() const {
		return root->sz - 2;
	}
	void erase(Node* &x) {
		if (x == null_s) return;

		/* 回收，放入内存池 */
		Node **fr = que, **ta = que, *fa = x->pre;
		*ta++ = x;
		while (fr < ta) {
			Node *tx = *fr++;
			pool[++top] = tx;
			if (tx->ch[0] != null_s) *ta++ = tx->ch[0];
			if (tx->ch[1] != null_s) *ta++ = tx->ch[1];
		}
		x = null_s;
		if (fa != null_s) pushUp(fa);
	}
	void insert(int k, int val) {
		select(k, null_s);
		select(k+1, root);
		keyTree = newNode(val);
		keyTree->pre = root->ch[1];
		pushUp(root->ch[1]);
		pushUp(root);
	}
	void del(int k) {
		select(k, null_s);
		select(k+2, root);
		/* 回收，放入内存池 */
		erase(keyTree);
		pushUp(root);
	}
	void reverse(int l, int r) {
		select(l, null_s);
		select(r+2, root);
		keyTree->rev ^= 1;
	}
	void dfs(Node *x, int a[]) {
		if (x->sz == 1) {
			a[0] = x->val;
		} else if (x->sz > 1) {
			pushDown(x);
			dfs(x->ch[0], a);
			a[x->ch[0]->sz] = x->val;
			dfs(x->ch[1], a + x->ch[0]->sz + 1);
		}
	}
	void pre_order(int a[]) {
		select(1, null_s);
		select(root->sz, root);
		dfs(keyTree, a);
	}
	void travel(Node *x) {
		if (x == null_s) return;
		travel(x->ch[0]);
		printf("%d ", x->val);
		travel(x->ch[1]);
	}
	
	Node* newNode(int val) {
		Node *x;
		if (top > -1) x = pool[top--];
		else x = mem + m_cnt++;
		x->pre = x->ch[0] = x->ch[1] = null_s;
		x->sz = 1;
		x->val = val;
		x->rev = 0;
		return x;
	}
	void makeTree(Node* &x, Node *f, int a[], int l, int r) {
		if (l > r) return;
		int m = (l + r) >> 1;
		x = newNode(a[m]);
		x->pre = f;
		makeTree(x->ch[0], x, a, l, m-1);
		makeTree(x->ch[1], x, a, m+1, r);
		pushUp(x);
	}
	void init(int n, int a[]) {
		// null_s 是特殊的叶节点，表示无，避免特判,因为有些操作要避免NULL
		null_s = mem;
		null_s->pre = null_s->ch[0] = null_s->ch[1] = null_s;
		null_s->sz = 0;
		null_s->val = 0;
		m_cnt = 1;
		top = -1;
		// 开头和末尾添加两个节点，避免特判，方便取区间，但是节点数变为n+2
		root = newNode(-1);
		root->ch[1] = newNode(-1);
		root->ch[1]->pre = root;
		root->sz = 2;

		makeTree(keyTree, root->ch[1], a, 0, n-1);
		pushUp(root->ch[1]);
		pushUp(root);
	}
};
/* 输入输出外挂 */
template <class T>
int scan_i(T &x) {
	int ch;
	bool ne = false;
	while (EOF != (ch = getchar()) && ('0' > ch || ch > '9') && ch != '-') ;
	if (EOF == ch) return EOF;
	if (ch == '-') {
		ne = 1;
		ch = getchar();
	}
	x = 0;
	while ('0' <= ch && ch <= '9') {
		x *= 10;
		x += ch - '0';
		ch = getchar();
	}
	if (ne) x = -x;
	return 1;
}
template <class T>
int print_i(const T &t) {
	T x = t;
	int l = 0, i;
	bool ne = false;
	if (x == (T)0) {
		putchar('0');
		l = 1;
	} else {
		if (x < 0) {
			putchar('-');
			x = -x;
			ne = true;
		}
		char buf[32];
		while (x > 0) {
			buf[l++] = '0' + x % 10;
			x /= 10;
		}
		for (i = l-1; i >= 0; --i) putchar(buf[i]);
	}
	return ne? l+1 : l;
}

SplayTree spt;
int a[MAXN];

int main() {
	int runs;
	scan_i(runs);
	while (runs--) {
		int n, m, l, r, sz;
		scan_i(n);
		for (int i = 0; i < n; ++i) {
			scan_i(a[i]);
		}
		spt.init(n, a);

		scan_i(l);
		scan_i(r);
		scan_i(m);
		while (m--) {
			char ch, cmd[31];
			int x;
			scanf("%s", cmd);
			if (cmd[0] == 'M') { /* Move */
				ch = cmd[4];
				scanf("%s", cmd);
				if (ch == 'L') { /* Left */
					if (cmd[0] == 'L') {
						--l;
					} else {
						--r;
					}
				} else { /* Right */
					if (cmd[0] == 'L') {
						++l;
					} else {
						++r;
					}
				}
			} else if (cmd[0] == 'I') { /* Insert */
				scanf("%s", cmd);
				scan_i(x);
				++r;
				if (cmd[0] == 'L') {
					spt.insert(l, x);
				} else {
					spt.insert(r, x);
				}
			} else if (cmd[0] == 'D') { /* Delete */
				scanf("%s", cmd);
				if (cmd[0] == 'L') {
					spt.del(l);
				} else {
					spt.del(r);
				}
				--r; /* 删掉一个元素后，r应该减小 */
			} else if (cmd[0] == 'R') { /* Reverse */
				spt.reverse(l, r);
			} else {
				Node *x = 0;
				for(;;) x->pre = 0;
			}
		}
		/* Ouptut Answer */
		spt.pre_order(a);
		sz = spt.size();
		for (int i = 0; i < sz; ++i) {
			if (i) putchar(' ');
			print_i(a[i]);
		}
		puts("");
	}
	return 0;
}
