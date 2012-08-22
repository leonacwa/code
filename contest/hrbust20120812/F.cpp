/* Printer Queue
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 105;

struct Node {
	int p, i;
	Node *next;
} p[MAXN];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int n, my;
		scanf("%d%d", &n, &my);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &p[i].p);
			p[i].i = i;
		}
		Node *head = NULL, *tail = p + n - 1;;
		for (int i = n-1; i >= 0; --i) {
			p[i].next = head;
			head = p + i;
		}
		int cnt = 0;
		while (head) {
			Node *nxt, *max_t = head;
			for (nxt = head->next; nxt; nxt = nxt->next) {
				if (max_t->p < nxt->p) {
					max_t = nxt;
				}
			}
			if (head == max_t) {
				++cnt;
				if (head->i == my) break;
				head = head->next;
			} else {
				while (head != max_t) {
					nxt = head->next;
					head->next = NULL;
					tail->next = head;
					tail = head;
					head = nxt;
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}

