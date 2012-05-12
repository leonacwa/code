/* poj 1032 Parliament */
#include <stdio.h>
int main()
{
    int n, i, k;

    scanf("%d", &n);
    for (k = 2; n-k >= 0; k++) {
        n -= k;
    }
    if (n == 0) {
        for (i = 2; i < k; i++) {
            printf("%d ", i);
        }
    }
    else if (n == k-1) {
        for (i = 3; i < k; i++) {
            printf("%d ", i);
        }
        printf("%d", k+1);
    }
    else if (1 <= n && n < k-1){
        for (i = 2; i < k-n; i++) {
            printf("%d ", i);
        }
        for (i++; i <= k; i++ ){
            printf("%d ", i);
        }
    }
    return 0;
}
