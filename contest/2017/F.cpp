#include <stdio.h>
#include <string.h>

const int MAXN = 100+5;
int a[MAXN];
int st[MAXN];
int top;
int n;

int main()
{
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		top = -1;
		int j = 0;
		for (int i = 1; i <= n; i++) {
			st[++top] = i;
			while (top != -1 && j < n && st[top] == a[j]) {
				j++;
				top--;
			}
		}
		while (j < n && top != -1) {
			if (st[top] == a[j]) {
				j++;
				top--;
			} else {
				break;
			}
		}
		if (top == -1 && j == n) {
			printf("Yes\n");
		} else {
			printf("No\n");
		}
	}
	return 0;
}

