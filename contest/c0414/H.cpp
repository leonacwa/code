#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 100005;
int n, m, q;
int a_set[NN], b_set[NN], c_set[NN];

void init(int set[], int n)
{
	for (int i = 0; i <= n; ++i) {
		set[i] = i;
	}
}

int find(int set[], int x)
{
	if (set[x] != x) {
		set[x] = find(set, set[x]);
	}
	return set[x];
}
void join(int set[], int x, int y)
{
	int fx = find(set, x), fy = find(set, y);
	if (fx != fy) {
		set[fy] = fx;
	}
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%d %d %d", &n, &m, &q);
		init(a_set, n);
		init(b_set, n);
		init(c_set, n);
		for (int i = 0; i < m; ++i) {
			int u, v;
			char c;
			scanf("%d %d %c", &u, &v, &c);
			if (c == 'a') {
				join(a_set, u, v);
			} else if (c == 'b') {
				join(a_set, u, v);
				join(b_set, u, v);
			} else if (c == 'c') {
				join(a_set, u, v);
				join(b_set, u, v);
				join(c_set, u, v);
			}
		}
		for  (int i = 0; i < q; ++i) {
			int u, v, fu, fv;
			char c = 0;
			scanf("%d %d", &u, &v);
			fu = find(c_set, u);
			fv = find(c_set, v);
			if (fu != fv) {
				fu = find(b_set, u);
				fv = find(b_set, v);
				if (fu != fv) {
					fu = find(a_set, u);
					fv = find(a_set, v);
					if (fu == fv) {
						c = 'a';
					}
				} else {
					c = 'b';
				}
			} else {
				c = 'c';
			}
			if (c == 0) {
				printf("-1\n");
			} else {
				printf("%c\n", c);
			}
		}
	}
	return 0;
}

