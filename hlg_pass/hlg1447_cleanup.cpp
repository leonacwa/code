#include <cstdio>
#include <cstring>
const int MAXN = 20 * 1000 * 4;
struct Node {
	bool del, f, delson;
	Node * son[64];
} node[MAXN];
int nNode;
Node *root;

char ch_id[256];

Node *newNode()
{
	Node * ptr = node + nNode++;
	ptr->del = false;
	ptr->delson = false;
	ptr->f = false;
	memset(ptr->son, 0, sizeof(ptr->son[0])*64);
	return ptr;
}

void insert(const char *s, bool del)
{
	Node * ptr = root, *p2;
	while (*s) {
		if (!del) ptr->delson = false;
		int i = ch_id[*s];
		if (NULL == ptr->son[i]) {
			p2 = newNode();
			p2->delson = del;
			ptr->son[i] = p2;
		}
		ptr = ptr->son[i];
		++s;
	}
	if (!del) ptr->delson = false;
	ptr->del = del;
	ptr->f = true;
}

int cal(const Node *rt)
{
	if (rt->delson) return 1;
	int sum = 0;
	if (rt->f && rt->del) sum = 1;
	for (int i = 0; i < 64; ++i) {
		if (rt->son[i]) {
			sum += cal(rt->son[i]);
		}
	}
	return sum;
}

int main()
{
	int id = 0;
	for (char ch = '0'; ch <= '9'; ++ch) ch_id[ch] = id++;
	for (char ch = 'A'; ch <= 'Z'; ++ch) ch_id[ch] = id++;
	for (char ch = 'a'; ch <= 'z'; ++ch) ch_id[ch] = id++;
	ch_id['.'] = id++;
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		nNode = 0;
		root = newNode();
		root->delson = true;
		int n;
		char str[32];
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			insert(str, true);
		}
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			insert(str, false);
		}
		printf("%d\n", cal(root));
	}
	return 0;
}

