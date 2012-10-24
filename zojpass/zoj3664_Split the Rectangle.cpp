/*
 * ZOJ 3664 Split the Rectangle
 * */
#include <cstdio>
#include <cstring>
#include <cassert>

const int MAXN = 1005;

struct Rect {
	int xl, yl, xr, yr;
	void show() const {
		printf("%d %d %d %d\n", xl, yl, xr, yr);
	}
};

struct TreeNode {
	TreeNode *l, *r, *p;
	int cnt, h;
	Rect rc;
};
int nTs;
TreeNode *root, T[MAXN * 4];

bool in_rect(const Rect &rc, int x, int y) {
	return rc.xl <= x && x <= rc.xr && rc.yl <= y && y <= rc.yr;
}

void insert(TreeNode *rt, int x1, int y1, int x2, int y2) {
	assert(rt!=NULL);
	if (rt->cnt == 0) {
		TreeNode *l = T + nTs++, *r = T + nTs++;
		l->p = r->p = rt;
		l->l = l->r = r->l = r->r = NULL;
		l->cnt = r->cnt = 0;
		l->h = r->h = rt->h + 1;
		l->rc.xl = rt->rc.xl; l->rc.yl = rt->rc.yl;
		r->rc.xr = rt->rc.xr; r->rc.yr = rt->rc.yr;
		if (x1 == x2) {
			l->rc.xr = x1; l->rc.yr = rt->rc.yr;
			r->rc.xl = x1; r->rc.yl = rt->rc.yl;
		} else {
			l->rc.xr = rt->rc.xr; l->rc.yr = y1;
			r->rc.xl = rt->rc.xl; r->rc.yl = y1;
		}
		/*
		printf("New\n");
		l->rc.show();
		r->rc.show();
		*/
		rt->l = l, rt->r = r;
	} else {
		assert(rt->l != NULL);
		if (in_rect(rt->l->rc, x1, y1) && (in_rect(rt->l->rc, x2, y2))) {
			insert(rt->l, x1, y1, x2, y2);
		} else {
			insert(rt->r, x1, y1, x2, y2);
		}
	}
	rt->cnt++;
}

TreeNode* find(TreeNode* rt, int x, int y) {
	assert(rt);
	if (rt->cnt == 0) {
		return rt;
	} else {
		if (in_rect(rt->l->rc, x, y)) {
			return find(rt->l, x, y);
		} else {
			return find(rt->r, x, y);
		}
	}
}

TreeNode* get_lca(TreeNode *a, TreeNode *b) {
	while (a != b) {
		if (a->h > b->h) a = a->p;
		else b = b->p;
	}
	return a;
}

int main() {
	int n, q;
	int x1, y1, x2, y2;
	while (EOF != scanf("%d%d%d%d", &x1, &y1, &x2, &y2)) {
		nTs = 1;
		root = T;
		root->rc.xl = x1;
		root->rc.yl = y1;
		root->rc.xr = x2;
		root->rc.yr = y2;
		root->cnt = 0;
		root->h = 0;
		root->p = NULL;
		root->l = root->r = NULL;
		scanf("%d%d", &n, &q);
		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			insert(root, x1, y1, x2, y2);
		}
		for (int i = 0; i < q; ++i) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			TreeNode *r1 = find(root, x1, y1), *r2 = find(root, x2, y2);
			TreeNode* rt = get_lca(r1, r2);
			/*
			printf("f %d %d\n", x1, y1);
			r1->rc.show();
			printf("f %d %d\n", x2, y2);
			r2->rc.show();
			rt->rc.show();
			printf("rt h %d\n", rt->h);
			printf("%p %p %p\n", rt, r1, r2);
			*/
			printf("%d\n", 1 + n - rt->cnt);
		}
	}
	return 0;
}
