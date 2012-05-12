/* poj 1740 A New Stone Game */
#include <stdio.h>
int a[10], n;
int main()
{
    int i, j, k, win;
    while (~scanf("%d", &n) && n) {
        for (i = 0; i < n; i++) {
            scanf("%d", a+i);
        }
        win = 1;
        if (n%2 == 0) {
            for (i = 0; i < n-1; i++) {
                k = i;
                for (j = i+1; j < n; j++) {
                    if (a[k] > a[j])
                        k = j;
                }
                if (i != k) {
                    j = a[i];  a[i] = a[k];  a[k] = j;
                }
            }
            win = 0;
            for (i = n/2 - 1; i >= 0; i--) {
                if (a[2*i] != a[2*i+1]) {
                    win = 1;
                    break;
                }
            }
        }
        printf("%d\n", win);
    }
    return 0;
}
