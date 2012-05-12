#include <stdio.h>
#include <string.h>

typedef struct _DLLNode {
	int a;
	struct _DLLNode *prev, *next;
} DLLNode;

typedef struct _DLLHead {
	int cnt;
	DLLNode *front, *tail;
} DLLHead;


void addToDLL(DLLHead *head, int a)
{
	DLLNode *ptr = malloc(sizeof(DLLNode));
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

/* Selection sort
 **/
void DLLSort(DLLHead *head)
{
	DLLNode *p1, *p2, *tmp, *p;
	for (p1 = head->front; p1 != NULL; p1 = p1->next) {
		p2 = p1;
		for (p = p1->next; p != NULL; p = p->next) { // find minimum
			if (p->a < p2->a) {
				p2 = p;
			}
		}
		if (p2 != p1) { // if found minimum, exchanage p1 and p2
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
			if (p1->next == p2) {
				p2->prev = p1->prev;
				p1->next = p2->next;
				p2->next = p1;
				p1->prev = p2;
			} else {
				p1->next->prev = p2;
				p2->prev->next = p1;

				tmp = p1->next;
				p1->next = p2->next;
				p2->next = tmp;

				tmp = p1->prev;
				p1->prev = p2->prev;
				p2->prev = tmp;
			}
			p1 = p2;
		}
	}
}

void DeleteDLL(DLLHead *head)
{
	DLLNode *ptr, *pt;
	for (ptr = head->front; ptr != NULL;) {
		//	printf("del %x\n", ptr);
		pt = ptr->next;
		free(ptr);
		ptr = pt;
	}
	head->front = head->tail = NULL;
	head->cnt = 0;
}

void PrintDLL(DLLHead *head)
{
	DLLNode * ptr;
	printf("Total %d:", head->cnt);
	for (ptr = head->front; ptr != NULL; ptr = ptr->next) {
		printf(" %d", ptr->a);
	}
	puts("");
}

int main()
{
	int n, i, a, nCase = 0;
	DLLHead *head = malloc(sizeof(DLLHead));
	head->front = head->tail = NULL;
	head->cnt = 0;
	printf("Please input number of integers:");
	while (EOF != scanf("%d", &n) && n > 0) {
		printf("Please input %d integers:", n);
		for (i = 0; i < n; ++i) {
			scanf("%d", &a);
			addToDLL(head, a); // add a integer to the tail of doubly linik list
		}
		//printf("Case %d\n", ++nCase);
		printf("Before Sort:\n");
		PrintDLL(head); // output unsorted doubly link list
		DLLSort(head); // sort doubly link list
		printf("After Sort:\n");
		PrintDLL(head); // output sorted doubly link list
		DeleteDLL(head); // delete doubly link list
		puts("");
		printf("Please input number of integers:");
	}

	return 0;
}

