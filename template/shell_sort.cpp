#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int shell_sort(int a[], int len) {
	int i, j, t;
	int gap = len / 3 * 2;
	int cnt = 0;
	do {
		gap /= 2;
		for (i = gap; i < len; ++i) {
			t = a[i];
			j = i - gap;
			while (j >= 0 && a[j] > t) { // insert
				a[j+gap] = a[j];
				j -= gap;
				cnt++;
			}
			a[j+gap] = t;
		}
	} while (gap > 1);
	return cnt;
}

void print(int a[], int len) {
	int i;
	printf("%d ", a[0]);
	for (i = 1; i < len; ++i) {
		printf("%s ", a[i-1] <= a[i] ? "<=":">");
		printf("%d ", a[i]);
	}
	puts("");
}
void rand_data(int a[], int len) {
	int i;
	srand(time(0));
	for (i = 0; i < len; ++i) {
		a[i] = rand();
	}
}
#define MAXN 32
int main()
{

	int a[MAXN];
	int cnt;
	rand_data(a, MAXN);
	printf("befor:\n");
	print(a, MAXN);
	cnt = shell_sort(a, MAXN);
	printf("after shell sort, %d times\n", cnt);
	print(a, MAXN);
	return 0;
}
