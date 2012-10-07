#include <cstdio>
#include <cstring>

const int MAXN = 1000006;
/** 伸展树的节点 */
struct Node {
	Node *pre, *ch[2];
	int sz;
	/* 题目需要 */
	bool rev; /* 表示该区间是否翻转 */
	int val;
};

/* 用结构体封装的伸展树
 * 整个伸展树表示的区间范围是[1,n]，添加的两个辅助节点不必考虑，内部已经自动转换
 * */
struct SplayTree {
#define keyTree (root->ch[1]->ch[0])
	Node *root, *null_s; /* null_s作为特殊的空节点，代替NULL，这样就不必在代码中对NULL特判，方便代码编写 */
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

	/** 旋转操作，c=0表示左旋，逆时针，c=1表示右旋，顺时针 */
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
	/** 伸展的操作，将x节点转到f下，f要在x之上，f为null_s时表示x转为根 */
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
	/** 删除x节点，并将节点释放回内存池 */
	void erase(Node* &x) {
		if (x == null_s) return;
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
	/** 将val插入到k位置 */
	void insert(int k, int val) {
		select(k, null_s);
		select(k+1, root);
		keyTree = newNode(val);
		keyTree->pre = root->ch[1];
		pushUp(root->ch[1]);
		pushUp(root);
	}
	/** 删除k位置的数 */
	void del(int k) {
		select(k, null_s);
		select(k+2, root);
		/* 回收，放入内存池 */
		erase(keyTree);
		pushUp(root);
	}
	/** 翻转[l,r]区间 */
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
	/* 前序遍历 ，并将结果存入a[]
	 * */
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
	/** 用有n个元素的a[]构造，添加额外的两个辅助节点，但是对外还是表示[1,n]的区间范围 */
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
SplayTree spt;
int a[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	spt.init(n, a);
	return 0;
}
