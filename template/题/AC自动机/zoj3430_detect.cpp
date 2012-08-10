/* AC自动机
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef unsigned char UCHAR;

const int MAXN = 512 * 64 + 100;
const int MAX_CHILD = 256;

struct Node {
	int id;
	Node *son[MAX_CHILD], *fail;
} nd[MAXN];
int nd_cnt;

static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
UCHAR decb64[256];

void decodeblock(const UCHAR in[4], UCHAR out[3])
{
	out[0] = (decb64[in[0]] << 2) | (decb64[in[1]] >> 4);
	out[1] = (decb64[in[1]] << 4) | (decb64[in[2]] >> 2);
	out[2] = (decb64[in[2]] << 6) | decb64[in[3]];
}

int decode(const UCHAR *src, UCHAR *dst)
{
	if (src == dst || src == NULL || dst == NULL) return -1;
	int len = strlen((const char*)src);
	while (len % 4) ;
	int k = 0;
	while (src[len-k-1] == '=') ++k;
	for (int i = 0; i*4 < len; ++i) {
		decodeblock(src + i*4, dst + i*3);
	}
	dst[len] = 0;
	len = len / 4 * 3 - k;
	return len;
}

Node* newNode()
{
	Node *p = nd + nd_cnt++;
	memset(p, 0, sizeof(Node));
	return p;
}

void insert(Node *root, const UCHAR *s, int l, int id)
{
	Node * p = root;
	for (int i = 0; i < l; ++i) {
		if (p->son[s[i]] == NULL) {
			p->son[s[i]] = newNode();
		}
		p = p->son[s[i]];
	}
	p->id = id;
}

void AC_construct(Node *root)
{
	Node *p = root;
	queue<Node*> Q;
	for (int i = 0; i < MAX_CHILD; ++i) {
		if (p->son[i]) {
			p->son[i]->fail = root;
			Q.push(p->son[i]);
		} else {
			p->son[i] = root;
		}
	}
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		for (int i = 0; i < MAX_CHILD; ++i) {
			if (p->son[i]) {
				Q.push(p->son[i]);
				Node *v = p->fail;
				while (v->son[i] == NULL) v = v->fail;
				p->son[i]->fail = v->son[i];
			} else {
				p->son[i] = p->fail->son[i];
			}
		}
	}
}

int AC_find(Node *root, const UCHAR *s, int l, bool vis[])
{
	int ret = 0;
	Node *p = root, *q;
	for (int i = 0; i < l; ++i) {
		while (p->son[s[i]] == NULL) p = p->fail;
		q = p = p->son[s[i]];
		while (q != root) {
			if (q->id > 0 && !vis[q->id]) {
				vis[q->id] = true;
				++ret;
			}
			q = q->fail;
		}
	}
	return ret;
}

UCHAR src[3000], dst[3000]; // 这个数组开得小了
bool vis[512 + 21];

int main()
{
	for (int i = 0; i < 64; ++i) {
		decb64[cb64[i]] = i;
	}
	decb64['='] = 0;
	int n, m;
	while (EOF != scanf("%d", &n)) {
		nd_cnt = 0;
		Node *root = newNode();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", src);
			int l = decode(src, dst);
			//printf("%s<>%s<%d>\n", src, dst, l);
			insert(root, dst, l, i);
		}
		AC_construct(root);
		scanf("%d", &m);
		int ans = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%s", src);
			int l = decode(src, dst);
		//	printf("%s<>%s<%d>\n", src, dst, l);
			memset(vis, 0, sizeof(vis));
			int ret = AC_find(root, dst, l, vis);
			printf("%d\n", ret);
		}
		puts("");
	}
	return 0;
}

