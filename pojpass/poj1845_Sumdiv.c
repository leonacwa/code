/* poj 1845 Sumdiv */
#include <stdio.h>
#define MAXN 10000
#define MOD_M 9901
typedef long long LL;
int p[MAXN], c[MAXN], cp;
LL pow_mod(LL a, LL n)
{
    LL ret = 1, s = a;
    while (n) {
        if (n&1) {
            ret = (ret*s) % MOD_M;
        }
        if (n>>=1) {
            s = (s*s) % MOD_M;
        }
        else
            break;
    }
    return ret;
}
LL fact(LL a, LL n)
{
    if(a == 0) {
        return 0;
    }
    if (n < 1) {
        return 1;
    }
    if (n&1) {
        return (fact(a, n/2)*((1+pow_mod(a, n/2+1))%MOD_M)) % MOD_M;
    }
    else {
        return (fact(a, n-1)*a%MOD_M + 1) % MOD_M;
    }
}

int main()
{
    int i;
    LL a, b, ans, t;
    scanf("%I64d %I64d", &a, &b);
    for (cp = 0, i = 2; i*i <= a; i++) if (a%i == 0){
        p[cp] = i;
        c[cp] = 1;
        a /= i;
        while (a%i == 0) {
            a /= i;
            c[cp]++;
        }
        cp++;
    }
    if (a > 1) {
        p[cp] = a;
        c[cp++] = 1;
    }
    ans = a!=0;
    for (i = 0; i < cp; i++) {
        ans = (ans * fact(p[i], c[i]*b)) % MOD_M;
    }
    printf("%I64d\n", ans);
    return 0;
}
