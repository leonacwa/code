#include <stdio.h>
#include <string.h>

typedef struct _DENode {
	int a;
	struct _DENode *prev, *next;
} DENode;

typedef struct _DEHead {
	int cnt;
	struct _DENode *front, *tail;
} DEHead;


void addLink(DEHead *head, int a)
{
	DENode *ptr = malloc(sizeof(DENode));
	ptr->a = a;
	ptr->next = NULL;
	if (head->tail == NULL) {
		head->cnt = 1;
		head->front = head->tail = ptr;
		ptr->prev = NULL;
	} else {
		head->cnt++;
		ptr->prev = head->tail;
		head->tail->next = ptr;
		head->tail = ptr;
	}
}

void DELinkSort(DEHead *head)
{
	DENode *p1, *p2, *tmp;
	for (p1 = head->front; p1 != NULL; p1 = p1->next) {
		for (p2 = p1->next; p2 != NULL; p2 = p2->next) {
			if (p2->a < p1->a) {
				if (p1->next == p2) {
					if (p1->prev == NULL) {
						head->front = p2;
					} else {
						p1->prev->next = p2;
					}
					if (p2->next == NULL) {
						head->tail = p1;
					} else {
						p2->next->prev = p1;
					}
					p2->prev = p1->prev;
					p1->next = p2->next;
					p2->next = p1;
					p1->prev = p2;
				} else {
					if (p1->prev == NULL) {
						head->front = p2;
					} else {
						p1->prev->next = p2;
					}
					if (p2->next == NULL) {
						head->tail = p1;
					} else {
						p2->next->prev = p1;
					}
					p1->next->prev = p2;
					p2->prev->next = p1;

					tmp = p1->next;
					p1->next = p2->next;
					p2->next = tmp;

					tmp = p1->prev;
					p1->prev = p2->prev;
					p2->prev = tmp;
				}
				tmp = p1;
				p1 = p2;
				p2 = tmp;
			}
		}
	}
}

void DeleteDELLink(DEHead *head)
{
	DENode *ptr, *pt;
	for (ptr = head->front; ptr != NULL;) {
	//	printf("del %x\n", ptr);
		pt = ptr->next;
		free(ptr);
		ptr = pt;
	}
	head->front = head->tail = NULL;
	head->cnt = 0;
}

void PrintDELink(DEHead *head)
{
	DENode * ptr;
	printf("Total %d:", head->cnt);
	for (ptr = head->front; ptr != NULL; ptr = ptr->next) {
		printf(" %d", ptr->a);
	}
	puts("");
}

int main()
{
	int n, i, a;
	DEHead *head = malloc(sizeof(DEHead));
	head->front = head->tail = NULL;
	head->cnt = 0;

	while (EOF != scanf("%d", &n) && n > 0) {
		for (i = 0; i < n; ++i) {
			scanf("%d", &a);
	//		printf("add %d\n", a);
			addLink(head, a);
		}
	}
	PrintDELink(head);
	DELinkSort(head);
	PrintDELink(head);
	DeleteDELLink(head);
	return 0;
}

