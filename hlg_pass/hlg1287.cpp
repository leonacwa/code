#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MP = 10000007;
struct Node {
	int d;
	Node* next;
};
Node* pnd[MP+1];
Node nd[MP+1];
int n_cnt;
int a[5000000+1];
int a_cnt;

int main()
{
	int n, d, p;
	while (EOF != scanf("%d", &n)) {
		memset(pnd, 0, sizeof(pnd));
		n_cnt = 0;
		a_cnt = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &d);
			p = d % MP;
			bool found = false;
			Node *pt = pnd[p];
			while (pt) {
				if (pt->d == d) {
					found = true;
					break;
				}
				pt = pt->next;
			}
			if (!found) {
				nd[n_cnt].d = d;
				nd[n_cnt].next = pnd[p];
				pnd[p] = &nd[n_cnt];
				n_cnt++;
				a[a_cnt++] = d;
			}
		}
		sort(a, a+a_cnt);
		printf("%d\n%d", a_cnt, a[0]);
		for (int i = 1; i < a_cnt; ++i) {
			printf(" %d", a[i]);
		}
		printf("\n");
	}
	return 0;
}

