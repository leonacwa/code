/** poj 1017 Packets */
#include <stdio.h>
int main()
{
    int c3[4] = {0, 5, 3, 1};
    int cnt, a1, a2, a3, a4, a5, a6;
    while (6 == scanf("%d %d %d %d %d %d", &a1, &a2, &a3, &a4, &a5, &a6)) {
        if (!(a1 | a2| a3 | a4 | a5 | a6)) {
            break;
        }
        cnt = a6 + a5 + a4 + (a3+3)/4;
        a1 -= a5 * 11;
        a2 -= a4 * 5;
        if (a2 < 0) {
            a1 += a2 * 4;
            a2 = 0;
        }
        if (a3 % 4) {
            a2 -= c3[a3%4];
            a1 -= 36 - 9*(a3%4) - 4*c3[a3%4];
            if (a2 < 0) {
                a1 += a2 * 4;
                a2 = 0;
            }
        }
        if (a2 > 0) {
            cnt += (a2 + 8) / 9;
            if (a2 % 9) {
                a1 -= 4*(9-a2%9);
            }
        }
        if (a1 > 0) {
            cnt += (a1+35)/36;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
