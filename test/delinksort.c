#include <stdio.h>
#include <string.h>

typedef struct _DLLNode { // 双向链表的节点结构体
	int a; // 节点存的数
	struct _DLLNode *prev, *next; // prev 前向指针，指向前面的数，next 后向指针，指向后面的数
} DLLNode;

typedef struct _DLLHead { // 双向链表信息结构体
	int cnt; //链表中元素个数
	DLLNode *front, *tail; // front 双向链表的第一个元素的指针，tail 双向链表最后一个元素的指针
} DLLHead;


void addToDLL(DLLHead *head, int a) // 插入一个数到双向链表表尾
{
	DLLNode *ptr = malloc(sizeof(DLLNode));
	ptr->a = a;
	ptr->next = NULL;
	if (head->tail == NULL) { // 如果是第一次插入一个数，则需要对表头指针front设置初始值
		head->cnt = 1;
		head->front = head->tail = ptr;
		ptr->prev = NULL;
	} else { // 不是第一次插入，直接在最后一个元素之后添加即可
		head->cnt++;
		ptr->prev = head->tail;
		head->tail->next = ptr;
		head->tail = ptr;
	}
}

/* Selection sort
 **/
void DLLSort(DLLHead *head) // 双向链表排序，使用选择排序法
{
	DLLNode *p1, *p2, *tmp, *p;
	for (p1 = head->front; p1 != NULL; p1 = p1->next) {
		p2 = p1;
		for (p = p1->next; p != NULL; p = p->next) { // 在当前位置之后找一个最小的数，把对应指针记录在p2里
			if (p->a < p2->a) {
				p2 = p;
			}
		}
		if (p2 != p1) { // 找到最小数，并且不是当前的位置，则交换
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

void DeleteDLL(DLLHead *head) // 删除双向链表
{
	DLLNode *ptr, *pt;
	for (ptr = head->front; ptr != NULL;) { // 一个一个删除，从头到尾删除
		//	printf("del %x\n", ptr);
		pt = ptr->next; // 先保存下一个元素的指针
		free(ptr); // 删除当前节点ptr
		ptr = pt; // 下一个当前节点ptr
	}
	head->front = head->tail = NULL; // 最后把表头指针清空
	head->cnt = 0;
}

void PrintDLL(DLLHead *head) // 输出双向链表的数
{
	DLLNode * ptr;
	printf("Total %d:", head->cnt);
	for (ptr = head->front; ptr != NULL; ptr = ptr->next) { // 从双向链表的第一个元素开始，不断的输出
		printf(" %d", ptr->a); // 输出
	}
	puts("");
}

int main()
{
	int n, i, a, nCase = 0;
	//  初始化双向链表，初始时清空的
	DLLHead *head = malloc(sizeof(DLLHead));
	head->front = head->tail = NULL;
	head->cnt = 0;
	
	printf("Please input number of integers:"); // 输出 要输入多少个数的提示
	while (EOF != scanf("%d", &n) && n > 0) { // 输入数的个数，如果个数小于等于0，则退出程序
		for (i = 0; i < n; ++i) { // 一次输入n个数
			scanf("%d", &a);// 读入一个数
			addToDLL(head, a); // 将读入的数a查到双向链表中
		}
		//printf("Case %d\n", ++nCase);
		printf("Before Sort:\n");  // 排序前的顺序
		PrintDLL(head); // 输出排序前数的顺序
		DLLSort(head); // 对双向链表进行排序
		printf("After Sort:\n");  // 排序后的顺序
		PrintDLL(head); // 输出排序后的数的顺序
		DeleteDLL(head); // 排序结束，把双向链表删除，并且清空
		puts("");
		printf("Please input number of integers:");
	}

	return 0;
}

