/*poj 1093 Formatting Text */
#include <stdio.h>
#include <string.h>
#define MAX_WORD 81
#define MAXN (10000+1)
typedef struct _Word{
    char s[MAX_WORD];
    int l;
} Word;
Word wd[MAXN];
char buf[MAXN+1];
int width, ws;
int f[MAXN], b[MAXN], bc[MAXN], nb1[MAXN], nb2[MAXN];
int cnt;

void print(int x)
{
    int sp, p, i, j, st = x - b[x];
    if (st > 0) {
        print(st);
    }
    if (b[x] > 1) {
        p = bc[x] / (b[x] - 1);
        sp = bc[x] % (b[x] - 1);
    }
    for (i = st+1; i < x; i++) {
        printf("%s", wd[i].s);
        for (j = (i < x - sp); j <= p; j++) {
            putchar(' ');
        }
    }
    printf("%s\n", wd[x].s);
}
int main()
{
    int i, j, k, ls, p, sp, t, k1, k2;
    while (~scanf("%d", &width) && width) {
        if (cnt++) {
            puts("");
        }
        gets(buf);
        ws = 1;
        while (gets(buf) && buf[0] != '\0') {
            for (i = 0; buf[i];) {
               if (buf[i] == ' ') {
                   i++;
                   continue;
               }
               for (wd[ws].l = 0; buf[i] != ' ' && buf[i]; i++) {
                   wd[ws].s[wd[ws].l++] = buf[i];
               }
               wd[ws].s[wd[ws].l] = '\0';
               ws++;
            }
        }
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        for (i = 1; i < ws; i++) {
            ls = 0;
            for (k = 1; k <= i; k++) {
                ls += wd[i-k+1].l;
                if (k-1 > width - ls) {
                    break;
                }
                t = f[i-k];
                if (k == 1) {
                    t += 500 ;
                }
                else {
                    p = (width - ls) / (k - 1);
                    sp = (width - ls) % (k - 1);
                    t += (p-1) * (p-1) * (k - 1 - sp);
                    t += p * p * sp;
                }
                if (f[i] > t) {
                    f[i] = t;
                    b[i] = k;
                    bc[i] = width - ls;
                }
                else if (f[i] == t) {
                    for (k1 = -1, j = i; j > 0; j -= b[j]) {
                        nb1[++k1] = b[j];
                    }
                    for (nb2[k2=0] = k, j = i - k; j > 0; j -= b[j]) {
                        nb2[++k2] = b[j];
                    }
                    while (k1 >= 0 && k2 >= 0 && nb1[k1] == nb2[k2]) {
                        k1--;
                        k2--;
                    }
                    if (k1 >= 0 && k2 >= 0 && nb1[k1] < nb2[k2]) {
                        f[i] = t;
                        b[i] = k;
                        bc[i] = width - ls;
                    }
                }
            }
        }
        //printf("%d\n", f[ws-1]);
        print(ws-1);
    }
    return 0;
}
