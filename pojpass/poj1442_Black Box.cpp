/*
 * POJ 1442 Black Box
 * Treap应用
 * */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int MAXN = 30005;

struct TreapNode {
	TreapNode* ch[2];
	int sz, fix;
	int val;
	int ch_sz(int c) { return ch[c] ? ch[c]->sz : 0; } 
};

template <const int MAXN = 100005>
struct Treap {
	TreapNode *root;
	int mcnt, pcnt;
	TreapNode mem[MAXN], *pool[MAXN];

	TreapNode * new_node(int val = 0) {
		TreapNode *x;
		if (pcnt >= 0) x = pool[pcnt--];
		else x = mem + mcnt++;
		x->ch[0] = x->ch[1] = NULL;
		x->sz = 1;
		x->fix = rand();
		x->val = val;
		return x;
	}
	/* c=0 左旋，c=1右旋 */
	void rotate(TreapNode* &x, int c) {
		TreapNode * y = x->ch[!c];
		x->ch[!c] = y->ch[c];
		y->ch[c] = x;
		x = y;
		y = x->ch[c];
		y->sz = y->ch_sz(0) + y->ch_sz(1) + 1;
		x->sz = x->ch_sz(0) + x->ch_sz(1) + 1;
	}

	void init() {
		mcnt = 0;
		pcnt = -1;
		root = NULL;
	}

	void insert(TreapNode* &x, int val) {
		if (x == NULL) {
			x = new_node(val);
		} else if (val <= x->val) {
			insert(x->ch[0], val);
			x->sz++;
			if (x->ch[0]->fix < x->fix) rotate(x, 1);
		} else {
			insert(x->ch[1], val);
			x->sz++;
			if (x->ch[1]->fix < x->fix) rotate(x, 0);
		}
	}
	void insert(int val) {
		insert(root, val);
	}

	bool del(TreapNode* &x, int val) {
		if (NULL == x) return false;
		bool ret;
		if (x->val < val) {
			ret = del(x->ch[1], val);
		} else if (x->val > val) {
			ret = del(x->ch[0], val);
		} else {
			if (NULL == x->ch[0] || NULL == x->ch[1]) {
				pool[++pcnt] = x;/* 放入内存池进行删除 */
				if (NULL != x->ch[0]) x = x->ch[0];
				else x = x->ch[1];
				ret = true;
			} else {
				if (x->ch[0]->fix < x->ch[1]->fix) {
					rotate(x, 1);
					ret = del(x->ch[1], val);
				} else {
					rotate(x, 0);
					ret = del(x->ch[0], val);
				}
			}
		}
		if (ret) x->sz--;
		return ret;
	}

	int get_rank(TreapNode* x, int val, int cur) {
		if (val == x->val) {
			return x->ch_sz(0) + cur + 1;
		} else if (val < x->val) {
			return get_rank(x->ch[0], val, cur);
		} else {
			return get_rank(x->ch[1], val, cur + x->ch_sz(0) + 1);
		}
	}
	TreapNode* get_kth(TreapNode* x, int k) {
		int lsz = x->ch_sz(0);
		if (k <= lsz) {
			return get_kth(x->ch[0], k);
		} else if (k > lsz + 1) {
			return get_kth(x->ch[1], k - (lsz + 1));
		} else {
			return x;
		}
	}
	int get_kth(int k) {
		return get_kth(root, k)->val;
	}
	int size() {
		return root->sz;
	}
};

int a[MAXN], u[MAXN];
Treap<MAXN> tr;

int main() {
	int m, n;
	srand(time(0));
	while (EOF != scanf("%d%d", &m, &n)) {
		for (int i = 0; i < m; ++i) scanf("%d", &a[i]);
		for (int i = 0; i < n; ++i) scanf("%d", &u[i]);
		sort(u, u + n);
		tr.init();
		int j = 0, g = 0;
		for (int i = 0; i < m; ++i) {
			tr.insert(a[i]);
			int sz = tr.size();
			while (j < n && sz == u[j]) {
				++g;
				printf("%d\n", tr.get_kth(g));
				++j;
			}
			if (j == n) break;
		}
	}
	return 0;
}
