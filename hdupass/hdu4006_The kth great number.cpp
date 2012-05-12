/*The kth great number*/
#include <stdio.h>
#define MAXN 1000000

int a[MAXN+1], al;

void insert(int x)
{
    int i, j;
    for (i = 0; i < al; i++) {
        if (a[i] < x) break;
    }
    for (j = al; j > i; j--) {
        a[j] = a[j-1];
    }
    a[i] = x;
    al++;
}

int main()
{
    int t, n, k, i;
    char buf[32];
    while (~scanf("%d %d", &n, &k)) {
        al = 0;
        for (i = 0; i < n; i++) {
            scanf("%s", buf);
            if (buf[0] == 'I') {
                scanf("%d", &t);
                insert(t);
            } else {
                printf("%d\n", a[k-1]);
            }
        }
    }
    return 0;
}
