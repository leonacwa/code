#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;

struct Person {
	char name[24];
	int ci, co;
};
Person ap[1000+5];

struct Node {
	int v;
	Node *pre, *next;
};
Node Q[2000+5], *head, *tail;
int nQ;

int main()
{
	int nCase = 0;
	int n, m, p;
	while (EOF != scanf("%d", &n)) {
		map<string, int> ma;
		int cnt = 0;
		for (int ci = 1; ci <= n; ++ci) {
			scanf("%d", &m);
			for (int co = 1; co <= m; ++co) {
				scanf("%d", &p);
				for (int i = 0; i < p; ++i) {
					scanf("%s", ap[cnt].name);
					ap[cnt].ci = ci;
					ap[cnt].co = co;
					ma[ap[cnt].name] = cnt + 1;
					++cnt;
				}
			}
		}
		int q;
		scanf("%d", &q);
		char op[32], name[32];
		nQ = 0;
		head = tail = NULL;
		printf("Scenario #%d\n", ++nCase);
		while (q--) {
			scanf("%s", op);
			if (op[0] == 'i') {
				scanf("%s", name);
				Node * ptr = Q + nQ++;
				ptr->v = ma[name] - 1;
				ptr->pre = NULL;
				ptr->next = NULL;
				if (head == NULL) {
					head = tail = ptr;
					continue;
				}
				Node *ptr2 = tail;
				bool find = false;
				while (ptr2) {
					if (ap[ptr2->v].co == ap[ptr->v].co && ap[ptr2->v].ci == ap[ptr->v].ci) {
						find = true;
						break;
					}
					ptr2 = ptr2->pre;
				}
				if (!find) {
					ptr2 = tail;
					while (ptr2) {
						if (ap[ptr2->v].ci == ap[ptr->v].ci) {
							find = true;
							break;
						}
						ptr2 = ptr2->pre;
					}
				}
				if (find) {
					ptr->next = ptr2->next;
					ptr->pre = ptr2;
					ptr2->next = ptr;
					if (ptr->next) {
						ptr->next->pre = ptr;
					}
					if (ptr->next == NULL) {
						tail = ptr;
					}
				} else {
					tail->next = ptr;
					ptr->pre = tail;
					tail = ptr;
				}
			} else if (op[0] == 'o') {
				int num;
				scanf("%d", &num);
				while (head && num--) {
					puts(ap[head->v].name);
					head = head->next;
					if (head) {
						head->pre = NULL;
					} else {
						tail = NULL;
					}
				}
			} else while (1) puts("fuck");
		}
		puts("");
	}
	return 0;
}

