/*
 * HDU 4436 str2int
 * 2012 Asia Tianjin Regional Contest F.str2int
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 110005;
const int MOD = 2012;

struct Node {
	int way, sum;
	int len;
	Node *f, *ch[11];
};
Node *root, *last;
Node pool[MAXN*2];
int cnt;

void init() {
	root = last = pool;
	memset(root, 0, sizeof(Node));
	cnt = 1;
}
void append(char ch) { /* 添加一个字符到末尾，last为一个后缀终止态，沿着last->f走，经过的都是终止态 */
	int c = ch - '0';
	Node *p = last, *np = pool + cnt++;
	memset(np, 0, sizeof(Node));
	np->len = last->len + 1;
	last = np;
	for (; NULL != p && NULL == p->ch[c]; p = p->f) p->ch[c] = np;
	if (p == NULL) {
		np->f = root;
	} else {
		if (p->ch[c]->len == p->len+1) {
			np->f = p->ch[c];
		} else { /* 新建一个节点，避免接受不存在的后缀 */
			Node *q = p->ch[c], *nq = pool + cnt++;
			*nq = *q;
			nq->len = p->len + 1;
			q->f = np->f = nq;
			for (; NULL != p && p->ch[c] == q; p = p->f) p->ch[c] = nq;
		}
	}
}

char str[MAXN];
int idx[MAXN*2];

bool cmp_idx(const int &i, const int &j) {
	if (pool[i].len != pool[j].len) return pool[i].len < pool[j].len;
	return i < j;
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		init();
		for (int i = 0; i < n; ++i) {
			if (i > 0) append('9'+1);
			scanf("%s", str);
			for (int j = 0; str[j]; ++j) {
				append(str[j]);
			}
		}
		for (int i = 0; i < cnt; ++i) {
			idx[i] = i;
		}
		sort(idx, idx+cnt, cmp_idx);
		int ans = 0;
		for (int i = 1; i <= 9; ++i) {
			if (pool[0].ch[i] == NULL) continue;
			int k = pool[0].ch[i] - pool;
			pool[k].sum += i;
			pool[k].way++;
		}
		for (int id = 1; id < cnt; ++id) {
			int i = idx[id];
			ans += pool[i].sum;
			if (ans >= MOD) ans %= MOD;
			for (int j = 0; j < 10; ++j) {
				if (pool[i].ch[j] == NULL) continue;
				int k = pool[i].ch[j] - pool;
				pool[k].way += pool[i].way;
				pool[k].sum += pool[i].sum * 10 + pool[i].way * j;
				if (pool[k].sum >= MOD) pool[k].sum %= MOD;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
