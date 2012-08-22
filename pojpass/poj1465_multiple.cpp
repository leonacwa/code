#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int NN = 50000;
struct Node {
	int d, r;
	struct Node * pre;
};
int d[11];
bool rem[NN];
Node Q[NN];
char str[NN];
int main()
{
	int n, m;
	while (EOF != scanf("%d", &n)) {
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) {
			scanf("%d", &d[i]);
		}
		if (n == 0) {
			puts("0");
			continue;
		}
		sort(d, d + m);
		memset(rem, 0, sizeof(rem));
		int front = 0, tail = 1;
		bool ans = false;
		Q[0].d = -1;
		Q[0].r = 0;
		Q[0].pre = NULL;
		while (front < tail) {
			Node *ptr = Q + front++;
			for (int i = 0; i < m; ++i) {
				Node *ptr2 = Q + tail;
				if (ptr->pre == NULL && d[i] == 0) continue;
				ptr2->r = ((ptr->r) * 10 + d[i]) % n;
				if (!rem[ptr2->r]) {
					rem[ptr2->r] = true;
					ptr2->d = d[i];
					ptr2->pre = ptr;
					++tail;
					if (ptr2->r == 0) {
						ans = true;
						break;
					}
				}
			}
			if (ans) break;
		}
		if (ans) {
			int pos =  NN;
			str[--pos] = 0;
			for (Node * ptr = Q + tail - 1; ptr->pre; ptr = ptr->pre) {
				str[--pos] = ptr->d + '0';
			}
			puts(str+pos);
		} else {
			puts("0");
		}
	}
	return 0;
}

