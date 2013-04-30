/* POJ 3486 A Simple Problem with Integers
 * Splay Tree 实现
 * */

#include <cstdio>
#include <cstring>

typedef long long int64;

const int MAXN = 100005;

struct Node {
	Node *pre, *ch[2];
	int sz;
	int val, add;
	int64 sum;
};

struct SplayTree {
#define keyTree (root->ch[1]->ch[0])

	int cnt;
	Node mem[MAXN];
	Node *root, *null_leaf;

	void PushDown(Node *x) {
		if (x->add) {
			x->val += x->add;
			x->ch[0]->add += x->add;
			x->ch[1]->add += x->add;
			x->ch[0]->sum += (int64)(x->ch[0]->sz) * x->add;
			x->ch[1]->sum += (int64)(x->ch[1]->sz) * x->add;
			x->add = 0;
		}
	}

	void PushUp(Node *x) {
		if (x == null_leaf) puts("error null_leaf");
		x->sz = 1 + x->ch[0]->sz + x->ch[1]->sz;
		x->sum = x->add + x->val + x->ch[0]->sum + x->ch[1]->sum;
	}

	/* 旋转操作，c=0表示左旋，逆时针，c=1表示右旋，顺时针
	 * */
	void Rotate(Node *x, int c) {
		Node *y = x->pre;
		PushDown(y);
		PushDown(x);
		y->ch[!c] = x->ch[c];
		if (x->ch[c] != NULL) x->ch[c]->pre = y;
		x->pre = y->pre;
		if (y->pre != NULL) y->pre->ch[ y->pre->ch[1] == y ] = x;
		x->ch[c] = y;
		y->pre = x;
		PushUp(y);
	}

	/* 将x转到f下，特别的x->pre==NULL表示的是根
	 * */
	void Splay(Node *x, Node *f) {
		PushDown(x);
		while (x->pre != f) {
			if (x->pre->pre == f) {
				Rotate(x, x->pre->ch[0] == x);
			} else {
				Node *y = x->pre, *z = y->pre;
				int c = (z->ch[0] == y);
				if (y->ch[c] == x) {
					Rotate(x, !c), Rotate(x, c); // 之字形旋转 
				} else {
					Rotate(y, c), Rotate(x, c); // 一字形旋转
				}
			}
		}
		PushUp(x);
		//if (f == NULL) root = x;
		if (f == null_leaf) root = x;
	}
	/* 选择第k个节点，并转到f下
	 * */
	void Select(int k, Node *f) {
		Node *x = root;
		while (x->ch[0]->sz + 1 != k) {
			PushDown(x);
			int sz = x->ch[0]->sz;
			if (k <= sz) {
				x = x->ch[0];
			} else {
				k -= sz + 1;
				x = x->ch[1];
			}
		}
		Splay(x, f);
	}

	Node* newNode(int val) {
		Node *x = mem + cnt++;
		x->pre = x->ch[0] = x->ch[1] = null_leaf;
		//x->pre = NULL;
		x->sz = 1;
		x->add = 0;
		x->sum = x->val = val;
		return x;
	}

	void MakeTree(Node* &x, int l, int r, Node *f, int a[]) {
		if (l > r) return;
		int m = (l + r) >> 1;
		x = newNode(a[m]);
		x->pre = f;
		MakeTree(x->ch[0], l, m-1, x, a);
		MakeTree(x->ch[1], m+1, r, x, a);
		PushUp(x);
	}
	void init(int n, int a[]) {
		// null_leaf 是特殊的叶节点，表示无，避免特判,因为有些不能有个NULL节点
		null_leaf = mem;
		memset(null_leaf, 0, sizeof(*null_leaf));
		null_leaf->pre = null_leaf;
		cnt = 1;
		// 开头和末尾添加两个节点，避免特判，方便取区间，但是节点数变为n+2
		root = newNode(-1);
		root->ch[1] = newNode(-1);
		root->ch[1]->pre = root;
		root->sz = 2;

		MakeTree(keyTree, 0, n-1, root->ch[1], a);
		PushUp(root->ch[1]);
		PushUp(root);
	}

	int64 Query(int a, int b) {
		Select(a, null_leaf);
		Select(b+2, root);
		return keyTree->sum;
	}

	void Add(int a, int b, int c) {
		Select(a, null_leaf);
		Select(b+2, root);
		keyTree->add += c;
		keyTree->sum += (int64) c * root->ch[1]->ch[0]->sz;
	}
};

SplayTree spt;
int a[MAXN];

int main() {
	int n, q;
	while (EOF != scanf("%d%d", &n, &q)) {
		for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
		spt.init(n, a);
		while (q--) {
			char cmd[3];
			int a, b, c;
			scanf("%s%d%d", cmd, &a, &b);
			if (cmd[0] == 'Q') {
				printf("%lld\n", spt.Query(a, b));
			} else {
				scanf("%d", &c);
				spt.Add(a, b, c);
			}
		}
	}
	return 0;
}
