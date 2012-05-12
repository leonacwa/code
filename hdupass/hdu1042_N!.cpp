/*N!*/
#include <stdio.h>
int a[50000];
void mul(int a[], int x)
{
    int i;
    a[1] *= x;
    for (i = 2; i <= a[0]; i++) {
        a[i] *= x;
        a[i] += a[i-1] / 10;
        a[i-1] %= 10;
    }
    while (a[a[0]] >= 10) {
        a[a[0]+1] = a[a[0]] / 10;
        a[a[0]] %= 10;
        a[0]++;
    }
}

int main()
{
    int n, i;
    while (~scanf("%d", &n)) {
        a[0] = 1;
        a[1] = 1;
        for (i = 2; i <= n; i++)   mul(a, i);
        for (i = a[0]; i > 0; i--)  printf("%d", a[i]);
        printf("\n");
    }
    return 0;
}
