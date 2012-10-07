#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
typedef int data_t;

void swap(data_t &A, data_t &B)
{
	data_t t = A;
	A = B;
	B = t;
}

/* 快排
 * */
void QuickSort(data_t *first, data_t *last)
{
	if (first == NULL || last == NULL) return;
	if (first >= last) return;
	srand(time(0));
	data_t *val = first + rand() % (last + 1 - first);
	swap(*val, *last);
	data_t *next = first;
	for (data_t *cur = first; cur != last; ++cur) {
		if (*cur < *last) {
			if (next != cur) {
				swap(*next, *cur);
			}
			++next;
		}
	}
	if (next == last) { // 要保证左右两个区间至少有一个元素
		--next;
	} else {
		swap(*next, *last);
	}
	if (first < next) QuickSort(first, next);
	if (next+1 < last) QuickSort(next+1, last);
}

const int MAXN = 1000;
data_t A[MAXN];

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; ++i) {
			cin >> A[i];
		}
		cout << "Sort:" << endl;
		QuickSort(A, A + n - 1);
		for (int i = 0; i < n; ++i) {
			cout << A[i] << " ";
		}
		cout << endl;
	}
	return 0;
}

