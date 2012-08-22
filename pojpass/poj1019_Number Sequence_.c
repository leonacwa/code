/** poj 1019 Number Sequence */
#include<stdio.h>
int main()
{
    unsigned int tt, i, j, d, ld, len;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%d", &i);
        len = ld = 0;
        for (j = 1; ; j++) {
            d = j;
            while (d){
                ld++;
                d /= 10;
            }
            len += ld;
            if (i <= len) {
                ld = len - i;
                d = j;
                while (ld--) {
                    d /= 10;
                    if (d == 0){
                        d = --j;
                    }
                }
                printf("%d\n", d % 10);
                break;
            }
        }
    }
    return 0;
}
