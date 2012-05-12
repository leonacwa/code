#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000;

int r[MAXN+5];
struct Num {
	int v, c;
};
Num nn[MAXN+5];
int ans[MAXN+5][3];

inline bool cmpNum(const Num &a, const Num &b) {
	return a.c > b.c;
}

void make_heap(int f, int n) 
{
	int c = f * 2;
	Num tn = nn[f];
	while (c <= n) {
		if (c < n && cmpNum(nn[c+1], nn[c])) {
			c++;
		}
		if (cmpNum(nn[c], tn)){
			nn[f] = nn[c];
			f = c;
			c = f * 2;
		} else {
			break;
		}
	}
	nn[f] = tn;
}

void add(Num tn, int &p)
{
	p++;
	int c = p;
	while (c > 1 && cmpNum(tn, nn[c/2])) {
		nn[c] = nn[c/2];
		c /= 2;
	}
	nn[c] = tn;
}

Num pop(int &p)
{
	Num tn = nn[1];
	nn[1] = nn[p];
	p--;
	make_heap(1, p);
	return tn;
}

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &r[i]);
		}
		sort(r+1, r+n+1);
		int p = 1;
		nn[p].v = r[1];
		nn[p].c = 1;
		for (int i = 2; i <= n; i++) {
			if (nn[p].v == r[i]) {
				nn[p].c++;
			} else {
				nn[++p].v = r[i];
				nn[p].c = 1;
			}
		}
		for (int i = p/2; i > 0; i--) {
		   make_heap(i, p);
		}
		int k = 0;
		while (p >= 3) {
			Num ta[3]; 
			for (int i = 0; i < 3; i++) {
				ta[i] = pop(p);
				ta[i].c--;
				ans[k][i] = ta[i].v;
			}
			for (int i = 0; i < 3; i++) {
				if (ta[i].c > 0) {
					add(ta[i], p);
				}
			}
			sort(ans[k], ans[k]+3);
			k++;
		}
		printf("%d\n", k);
		for (int i = 0; i < k; i++) {
			printf("%d %d %d\n", ans[i][2], ans[i][1], ans[i][0]);
		}
	}
	return 0;
}

