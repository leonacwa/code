/* poj 3619 Speed Reading */
#include <stdio.h>
int min(int a, int b){return a<b?a:b;}
int main()
{
    int n, k, s, t, r, i, j;
    scanf("%d %d", &n, &k);
    while (3 == scanf("%d %d %d", &s, &t, &r)) {
        i = n / (s*t);
        j = n % (s*t);
        if (j == 0) {
            printf("%d\n", i*(t+r) - r);
        }
        else {
            printf("%d\n", i*(t+r) + j/s + (j%s != 0));
        }
    }
    return 0;
}
