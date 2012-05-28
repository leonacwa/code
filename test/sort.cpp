#include <stdio.h>

// —°‘Ò≈≈–Ú
void select_sort(int a[], int n)
{
	int i, j, k, t;
	for (int i = 0; i < n; ++i) {
		int k = i;
		for (int j = i + 1; j < n; ++j) {
			if (a[j] < a[k]) {
				k = j;
			}
		}
		if (i != k) {
			int t = a[i];
			a[i] = a[k];
			a[k] = t;
		}
	}
}
//  √∞≈›≈≈–Ú
void bubble_sort(int a[], int n)
{
	int i, j, t;
	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			if (a[j] < a[i]) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
}

