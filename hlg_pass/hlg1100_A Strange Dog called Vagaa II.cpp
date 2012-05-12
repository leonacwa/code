/// A Strange Dog called Vagaa II
/// http://acm.hrbust.edu.cn/showproblem.php?problemid=1100
#include <stdio.h>
#include <string.h>

#define _MOD 10007

struct Matrix_3{
    int a[3][3];
    int r, c;
};

void matrix_multi(struct Matrix_3 *a, const struct Matrix_3 *b)
{
    struct Matrix_3 ra, rb;
    memcpy(&ra, a, sizeof(ra));
    memcpy(&rb, b, sizeof(rb));
    
    int ai, aj, i, s;
    for (ai = 0; ai < ra.r; ai++){
        for (aj = 0; aj < ra.c; aj++){
            s = 0;
            for (i = 0; i < ra.c; i++){
                s += (ra.a[ai][i] * rb.a[i][aj]) % _MOD; /// 可能有负数
                s %= _MOD;
            }
            a->a[ai][aj] = s;
        }
    }
}
void matrix_pow(struct Matrix_3 *a, int n)
{
    int r, c, i;
    if (n == 0){
        r = a->r;
        c = a->c;
        memset(a, 0, sizeof(struct Matrix_3));
        a->r = r;
        a->c = c;
        for (i = r - 1; i >= 0; i--)
            a->a[i][i] = 1;
        return;
    }
    if (n == 1)
        return;
    if (n == 2){
        matrix_multi(a, a);
        return;
    }
    
     struct Matrix_3 ra;
     memcpy(&ra, a, sizeof(ra));
     
     matrix_pow(a, n / 2);
     matrix_multi(a, a);
     if (1 == n % 2)
         matrix_multi(a, &ra);
}
int main()
{
    struct Matrix_3 an;
    int n, ans, tt;
    
    scanf("%d", &tt);
    while (tt-- && 1 == scanf("%d", &n)){
        if (n == 0)
            ans = 1;
        else if (n == 1)
            ans = 2;
        else if (n == 2)
            ans = 4;
        else {
            memset(&an, 0, sizeof(an));
            an.r = an.c = 3;
            an.a[0][0] = 2;
            an.a[0][1] = 1;
            an.a[1][2] = 1;
            an.a[2][0] = -1;
            matrix_pow(&an, n-2);
            ans = (4 * an.a[0][0]) % _MOD + (2 * an.a[1][0]) % _MOD + 1 * an.a[2][0];
        }
        printf("%d\n", (_MOD * _MOD +ans) % _MOD);
    }
    return 0;
}
