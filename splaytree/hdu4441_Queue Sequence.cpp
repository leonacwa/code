/*
 * HDU 4441 Queue Sequence
 * Asia 2012 Tianjin K.Queue Sequence
 * 用平衡树做，不过我只会Splay，还不是很熟练。直接用了NOI2005维护数列的模板。
 *
  1.insert p
  在p位置插入一个没在序列中的最小正整数，因为n<=1e5，我就用一个树状数组去找了，二分找到最小的正整数a；
  然后插入a到p位置，还要插入-a，因为是队列，所以如果a之前有x个正整数，那么我们的-a就应该放在开始的x个负整数之后，要求-a尽量往右，那么我们找到第x+1个负整数的位置p_，然后插入到这个位置p_，因为可能没有第x+1负整数，所以注意特判。
  2.remove i
  把i和-i移除。我用一个数组记录i和-i对应的节点指针，删除时，先把节点splay到根，然后就能知道节点所在的序列位置，删除即可。
  3. query i
  求i和-i之间的数的和。跟remove一样，找到两数的位置后splay求和即可。

  写得好悲催！中间找不出错误，自己不够细心了，精力不够，撸不起。
  写了一个生成数据的程序，来验证自己的代码，老是程序崩溃，外加TLE。
  后来才发现，是push_up写错了，%>_<%

 * */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 200000 + 5;

struct TreeArray {
	int c[MAXN];
#define lowbit(x) ((x)&(-x))
	void add(int i, int v) {
		for (; i < MAXN; i += lowbit(i)) {
			c[i] += v;
		}
	}
	int sum(int i) {
		int s = 0;
		for (; i > 0; i -= lowbit(i)) {
			s += c[i];
		}
		return s;
	}
};

struct SplayTree {
	struct Node {
		Node *ch[2], *pre;
		int sz, psz, nsz;
		int val;
		int64 sum;
	};
#define keyTree (root->ch[1]->ch[0])
	Node *root, *null_node;
	Node mem[MAXN];
	Node *que[MAXN], *pool[MAXN];
	int mem_cnt, top;
	Node *vp[MAXN];
	int offset;

	void push_up(Node *x) {
		if (x == null_node) return;
		x->sz = 1;
		if (x->val > 0) {
			x->psz = 1, x->nsz = 0;
		} else if (x->val < 0) {
			x->psz = 0, x->nsz = 1;
		} else {
			x->psz = x->nsz = 0;
		}
		x->sum = x->val;
		for (int c = 0; c < 2; ++c) {
			if (x->ch[c] != null_node) {
				x->sz += x->ch[c]->sz;
				x->psz += x->ch[c]->psz;
				x->nsz += x->ch[c]->nsz;
				x->sum += x->ch[c]->sum;
			}
		}
	}
	/** 旋转操作，c=0表示左旋，逆时针，c=1表示右旋，顺时针 */
	void rotate(Node *x, int c) {
		Node *y = x->pre;
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
		push_up(f);
		if (f == null_node) root = x;
	}
	bool select(int k, Node *f) {
		Node *x = root;
		for (;;) {
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
		memset(x, 0, sizeof(Node));
		x->pre = x->ch[0] = x->ch[1] = null_node;
		vp[val+offset] = x;
		x->sz = 1;
		if (val > 0) x->psz = 1;
		else if (val < 0) x->nsz = 1;
		x->val = x->sum = val;
		return x;
	}
	void init(int n) {
		memset(vp, 0, sizeof(vp));
		offset = n;
		null_node = mem;
		memset(null_node, 0, sizeof(Node));
		null_node->pre = null_node->ch[0] = null_node->ch[1] = null_node;
		mem_cnt = 1, top = -1;

		// 开头和末尾添加两个节点，避免特判，方便取区间，但是节点数变为n+2
		root = new_node(0);
		root->ch[1] = new_node(-2*n-1);
		root->ch[1]->pre = root;
		push_up(root);

	}
	/* 将 实际 [l,r] 区间转到 keyTree */
	void ch_key_tree(int l, int r) {
		select(l, null_node);
		select(r+2, root);
	}
	void erase(Node * &x) {
		if (x == null_node) {
			return;
		}
		Node *f = x->pre, **fr = que, **ta = que;
		*ta++ = x;
		while (fr < ta) {
			Node *x = *fr++;
			vp[x->val + offset] = NULL;
			pool[++top] = x;
			if (x->ch[0] != null_node) *ta++ = x->ch[0];
			if (x->ch[1] != null_node) *ta++ = x->ch[1];
		}
		x = null_node;
		push_up(f);
	}
	void del(int pos, int tot) {
		ch_key_tree(pos, pos+tot-1);
		erase(keyTree);
		push_up(root);
	}
	int64 get_sum(int l, int r) {
		ch_key_tree(l, r);
		return keyTree->sum;
	}
	void pre_ord(Node *x) {
		if (x == null_node) return;
		for (int i = 0; i < 2; ++i)
			if (x->ch[i] != null_node && x->ch[i]->pre != x) {
				fprintf(stderr, "error pre %d(%p)<-%d(%p)\n", x->val, x, x->ch[i]->val, x->ch[0]);
				exit(-1);
			}
		if (x->sz != 1 + x->ch[0]->sz + x->ch[1]->sz) {
			fprintf(stderr, "error sz %d:%d  %p %d\n", x->sz, 1+x->ch[0]->sz+x->ch[1]->sz, x, x->val);
			exit(-1);
		}
		if (x->ch[0]) pre_ord(x->ch[0]);
		printf("%d ", x->val);
		//printf("%d(%p)  ", x->val, x);
		if (x->ch[1]) pre_ord(x->ch[1]);
	}
	void travel() {
		printf("travel() ");
		pre_ord(root);
		printf("\n");
	}

	/******************** Problem Operation **********/
	int get_sz(int t, int v) {
		//printf("get_sz %d %d\n", v, v + offset);
		if (vp[v+offset] == NULL) {
			fprintf(stderr, "vp %d %d\n", v, v + offset);
			//while (1);
			assert(vp[v+offset]);
		}
		splay(vp[v+offset], null_node);
		if (t == 0) return root->ch[0]->sz;
		else if (t > 0) return root->ch[0]->psz + 1;
		else return root->ch[0]->nsz + 1;
	}
	int get_size(int t, int l, int r) {
		ch_key_tree(l, r);
		if (t == 0) return keyTree->sz;
		else if (t > 0) return keyTree->psz;
		else return keyTree->nsz;
	}
	void ins(int p, int v) {
		//printf("ins %d %d\n", p, v);
		ch_key_tree(p, p-1);
		keyTree = new_node(v);
		keyTree->pre = root->ch[1];
		push_up(root->ch[1]);
		push_up(root);
	}
	int loc_ne(int no) {
		int l = 1, r = size();
		while (l < r) {
			int m = (l + r) >> 1;
			int s = get_size(-1, 1, m);
			if (s < no) {
				l = m + 1;
			} else {
				r = m;
			}
		}
		if (get_size(-1, 1, l) < no) ++l;
		return l;
	}
	void rm(int v) {
		//if (vp[v+offset] == NULL) return;
		int l = get_sz(0, v);
		del(l, 1);
	}
	int64 query(int i) {
		if (vp[i+offset] == NULL || vp[-i+offset] == NULL) return -1;
		int l = get_sz(0, i), r = get_sz(0, -i);
		//printf("query %d %d\n", l, r);
		return get_sum(l, r);
	}
};

SplayTree spt;
TreeArray ta;

int get_minp() {
	int l = 1, r = MAXN - 1;
	while (l < r) {
		int m = (l + r) >> 1;
		if (ta.sum(m) >= 1) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	return l;
}

int main() {
	int n, ncase = 0;
	while (EOF != scanf("%d", &n)) {
		++ncase;
		printf("Case #%d:\n", ncase);
		memset(ta.c, 0, sizeof(ta.c));
		for (int i = 1; i <= n; ++i) ta.add(i, 1);
		spt.init(n);

		for (int i = 0; i < n; ++i) {
			char cmd[32];
			int d;
			scanf("%s%d", cmd, &d);
			//	fprintf(stderr, "%d:%s %d\n", i, cmd, d);
			if ('i' == cmd[0]) { // insert p
				++d;
				int a = get_minp();
				ta.add(a, -1);
				spt.ins(d, a); // insert +a
				int as = spt.get_sz(1, a);
				int p_ = spt.loc_ne(as);
				//printf("loc %d => %d\n", as, p_);
				spt.ins(p_, -a);
			} else if ('r' == cmd[0]) { // remove d
				spt.rm(-d);
				spt.rm(d);
				ta.add(d, 1);
			} else if ('q' == cmd[0]) { // query d
				printf("%lld\n", spt.query(d));
			} else {
			}
			//		spt.travel(); puts("");
		}
	}
	return 0;
}
