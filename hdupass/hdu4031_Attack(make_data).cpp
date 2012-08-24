/* hdu4031 data */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAXN 20000
int main()
{
    int tt;
    int n, q, t, i;
    tt = 20;
    printf("%d\n", tt);
    while (tt--) {
        srand(time(0));
        n = MAXN; //(rand()-1) % MAXN + 1;
        q = MAXN;//(rand()-1) % MAXN + 1;
        t = (rand()-1) % 50 + 1;
        if (t == 0) t = 2;
        printf("%d %d %d\n", n, q, t);
        for (i = 0; i < q; i++) {
            if (rand()%2 == 0) {
                printf("Attack %d %d\n", (rand()-1) % n + 1, (rand()-1) % n + 1);
            }
            else {
                printf("Query %d\n", (rand()-1) % n + 1);
            }
        }
    }
    return 0;
}
