#include <stdio.h>
#include <string.h>

typedef struct _DLLNode { // ˫������Ľڵ�ṹ��
	int a; // �ڵ�����
	struct _DLLNode *prev, *next; // prev ǰ��ָ�룬ָ��ǰ�������next ����ָ�룬ָ��������
} DLLNode;

typedef struct _DLLHead { // ˫��������Ϣ�ṹ��
	int cnt; //������Ԫ�ظ���
	DLLNode *front, *tail; // front ˫������ĵ�һ��Ԫ�ص�ָ�룬tail ˫���������һ��Ԫ�ص�ָ��
} DLLHead;


void addToDLL(DLLHead *head, int a) // ����һ������˫�������β
{
	DLLNode *ptr = malloc(sizeof(DLLNode));
	ptr->a = a;
	ptr->next = NULL;
	if (head->tail == NULL) { // ����ǵ�һ�β���һ����������Ҫ�Ա�ͷָ��front���ó�ʼֵ
		head->cnt = 1;
		head->front = head->tail = ptr;
		ptr->prev = NULL;
	} else { // ���ǵ�һ�β��룬ֱ�������һ��Ԫ��֮����Ӽ���
		head->cnt++;
		ptr->prev = head->tail;
		head->tail->next = ptr;
		head->tail = ptr;
	}
}

/* Selection sort
 **/
void DLLSort(DLLHead *head) // ˫����������ʹ��ѡ������
{
	DLLNode *p1, *p2, *tmp, *p;
	for (p1 = head->front; p1 != NULL; p1 = p1->next) {
		p2 = p1;
		for (p = p1->next; p != NULL; p = p->next) { // �ڵ�ǰλ��֮����һ����С�������Ѷ�Ӧָ���¼��p2��
			if (p->a < p2->a) {
				p2 = p;
			}
		}
		if (p2 != p1) { // �ҵ���С�������Ҳ��ǵ�ǰ��λ�ã��򽻻�
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

void DeleteDLL(DLLHead *head) // ɾ��˫������
{
	DLLNode *ptr, *pt;
	for (ptr = head->front; ptr != NULL;) { // һ��һ��ɾ������ͷ��βɾ��
		//	printf("del %x\n", ptr);
		pt = ptr->next; // �ȱ�����һ��Ԫ�ص�ָ��
		free(ptr); // ɾ����ǰ�ڵ�ptr
		ptr = pt; // ��һ����ǰ�ڵ�ptr
	}
	head->front = head->tail = NULL; // ���ѱ�ͷָ�����
	head->cnt = 0;
}

void PrintDLL(DLLHead *head) // ���˫���������
{
	DLLNode * ptr;
	printf("Total %d:", head->cnt);
	for (ptr = head->front; ptr != NULL; ptr = ptr->next) { // ��˫������ĵ�һ��Ԫ�ؿ�ʼ�����ϵ����
		printf(" %d", ptr->a); // ���
	}
	puts("");
}

int main()
{
	int n, i, a, nCase = 0;
	//  ��ʼ��˫��������ʼʱ��յ�
	DLLHead *head = malloc(sizeof(DLLHead));
	head->front = head->tail = NULL;
	head->cnt = 0;
	
	printf("Please input number of integers:"); // ��� Ҫ������ٸ�������ʾ
	while (EOF != scanf("%d", &n) && n > 0) { // �������ĸ������������С�ڵ���0�����˳�����
		for (i = 0; i < n; ++i) { // һ������n����
			scanf("%d", &a);// ����һ����
			addToDLL(head, a); // ���������a�鵽˫��������
		}
		//printf("Case %d\n", ++nCase);
		printf("Before Sort:\n");  // ����ǰ��˳��
		PrintDLL(head); // �������ǰ����˳��
		DLLSort(head); // ��˫�������������
		printf("After Sort:\n");  // ������˳��
		PrintDLL(head); // �������������˳��
		DeleteDLL(head); // �����������˫������ɾ�����������
		puts("");
		printf("Please input number of integers:");
	}

	return 0;
}

