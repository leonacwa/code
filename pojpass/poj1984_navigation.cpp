#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 40005;
const int MAXK = 10005;
struct Node {
	int f, x, y;
};
Node node[MAXN];

struct Input {
	int a, b, l;
	char d;
};
Input input[MAXN];

struct Query {
	int a, b, d, i, o;
};
Query query[MAXK];
bool cmpQi(const Query &A, const Query &B) {
	return A.i < B.i;
}
bool cmpQo(const Query &A, const Query &B) {
	return A.o < B.o;
}

void init(int n)
{
	for (int i = 0; i <= n; ++i) {
		node[i].f = i;
		node[i].x = 0;
		node[i].y = 0;
	}
}

int find(int x)
{
	if (x == node[x].f) {
		return x;
	}
	int f = node[x].f;
	int nf = find(f);
	node[x].x += node[f].x;
	node[x].y += node[f].y;
	node[x].f = nf;
	return nf;
}

void join(int b, int a, int x, int y) // a <- b
{
	int fa = find(a), fb = find(b);
	if (fa != fb) {
		node[fb].f = fa;
		node[fb].x = x + node[a].x - node[b].x;
		node[fb].y = y + node[a].y - node[b].y;
	}
}

int main()
{
	int n, m;
	while (EOF != scanf("%d %d", &n, &m)) {
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d %c", &input[i].a, &input[i].b, &input[i].l, &input[i].d);
		}
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; ++i) {
			scanf("%d %d %d", &query[i].a, &query[i].b, &query[i].i);
		}
		sort(query, query + k, cmpQi);
		init(n);
		int j = 0;
		for (int i = 0; i < k; ++i) {
			while (j < m && j < query[i].i) {
				int x = 0, y = 0, l = input[j].l;
				switch (input[j].d) {
					case 'N':
						y = l;
						break;
					case 'S':
						y = -l;
						break;
					case 'W':
						x = -l;
						break;
					case 'E':
						x = l;
						break;
				}
				join(input[j].a, input[j].b, x, y);
				++j;
			}
			if (j == query[i].i) {
				int a = query[i].a, b = query[i].b;
				int fa = find(a);
				int fb = find(b);
				if (fa == fb) {
					query[i].d = abs(node[a].x - node[b].x) + abs(node[a].y - node[b].y);
				} else {
					query[i].d = -1;
				}
			}
		}
		sort(query, query + k, cmpQo);
		for (int i = 0; i < k; ++i) {
			printf("%d\n", query[i].d);
		}
	}
	return 0;
}

