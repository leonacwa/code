/* Find the maximum */
#include <stdio.h>
#include <string.h>
#include <math.h>
#define PRIMES 168
int prime[168]={
 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443,
 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647,
 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757,
 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983,
 991, 997};
int pro[PRIMES+1][256];

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

int cmp_num(int a[], int b[])
{
    if (a[0] != b[0]) return a[0] - b[0];
    int i;
    for (i = a[0]; i > 0; i--) {
        if (a[i] != b[i]) return a[i] - b[i];
    }
    return 0;
}
void p_num(int a[])
{
    int i;
    for (i = a[0]; i >= 1; i--) printf("%d", a[i]);
}

int main()
{
    int tt, i, j;
    char buf[256];
    int num[128];
    pro[0][0] = 1;
    pro[0][1] = 1;
    for (i = 1; i<= PRIMES; i++) {
        for (j = 0; j <= pro[i-1][0]; j++) pro[i][j] = pro[i-1][j];
        mul(pro[i], prime[i-1]);
    }
    scanf("%d", &tt);
    gets(buf);
    while (tt--) {
        gets(buf);
        num[0] = strlen(buf);
        for (i = num[0]-1; i >= 0; i--) {
            num[num[0] - i] = buf[i] -'0';
        }
        //p_num(num); printf("\n");
        for (i = 1; i <= PRIMES; i++) {
            if (cmp_num(pro[i], num) > 0) break;
        }
        p_num(pro[i-1]); printf("\n");
    }
    return 0;
}
/*
#define MAXP 1000
bool p[MAXP];
void get_prime()
{
    memset(p, 1, sizeof(p));
    int i, n = 0, j;
    p[0] = p[1] = 0;
    for (i = 2; i <= MAXP; i++) {
        if (p[i]) {
            prime[n++] = i, printf("%d, ", i);
            for (j = i+i; j <= MAXP; j+=i) p[j] = 0;
        }
    }
    printf("\n%d\n", n);
}
*/
