/*
 * POJ 3481 Double Queue
 * 两个堆，用关联映射之间的值
 * */
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

const int MAXN = 1000006;
struct KP {
	int val, id;
	int fix;
};
struct greaterKP {
	bool operator () (const KP &a, const KP &b) const {
		return a.val > b.val;
	}
};

struct lessKP {
	bool operator () (const KP &a, const KP &b) const {
		return a.val < b.val;
	}
};

int fix_cnt;
bool del[MAXN];
int sz_max, sz_min;
KP kp_max[MAXN], kp_min[MAXN];

template <class cmp>
int get(KP a[], int &sz) {
	while (sz > 0 && del[a[0].fix]) {
		pop_heap(a, a + sz, cmp());
		--sz;
	}
	if (sz == 0) return 0;
	else {
		del[a[0].fix] = 1;
		return a[0].id;
	}
}
template <class cmp>
void ins(KP a[], int &sz, const KP &tmp) {
	a[sz++] = tmp;
	push_heap(a, a+sz, cmp());
}

void init() {
	sz_max = sz_min = 0;
	fix_cnt = 0;
}

int main() {
	int cmd;
	while (EOF != scanf("%d", &cmd)) {
		if (cmd == 0) {
			continue;
		}
		if (cmd == 1) {
			int k, p;
			scanf("%d%d", &k, &p);
			KP t;
			t.val = p;
			t.id = k;
			t.fix = fix_cnt;
			del[fix_cnt++] = 0;
			ins<lessKP>(kp_max, sz_max, t);
			ins<greaterKP>(kp_min, sz_min, t);
		} else if (cmd == 2) {
			int a = get<lessKP>(kp_max, sz_max);
			printf("%d\n", a);
		} else if (cmd == 3) {
			int a = get<greaterKP>(kp_min, sz_min);
			printf("%d\n", a);
		} else {
		}
	}
	return 0;
}
