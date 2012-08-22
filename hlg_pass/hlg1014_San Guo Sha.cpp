/*San Guo Sha*/
#include <stdio.h>
#include <string.h>
#define MAXN 101
#define ZG 0
#define ZC 1
#define FZ 2
#define NJ 3

typedef struct _Role{
    int type, alive, score, ext;
}Role;
Role rl[MAXN];
int alive[4];

int get_type(const char *s)
{
    if (strcmp(s, "ZG") == 0) return ZG;
    if (strcmp(s, "ZC") == 0) return ZC;
    if (strcmp(s, "FZ") == 0) return FZ;
    if (strcmp(s, "NJ") == 0) return NJ;
    while(1)puts("fuck you");
}

int main()
{
    int tt;
    int i, j, a, b, n, m;
    char buf[16];
    scanf("%d", &tt);
    while (tt--) {
        memset(alive, 0, sizeof(alive));
        memset(rl, 0, sizeof(rl));

        scanf("%d %d", &n, &m);
        for (i = 0; i < n; i++)  {
            scanf("%s", buf);
            rl[i].score = 0;
            rl[i].ext = 0;
            rl[i].alive = 1;
            rl[i].type = get_type(buf);
            alive[rl[i].type]++;
        }
        for (i = 0; i < m; i++) {
            if (alive[ZG] == 0 || alive[FZ]+alive[NJ] == 0) break;
            scanf("%d %d", &a, &b);

            if (rl[a].type == ZG) { /* ZG */
                if (rl[b].type == FZ || rl[b].type == NJ)  rl[a].ext++;
                if (rl[b].type == NJ && alive[NJ] == 1 && (alive[ZC]+alive[FZ] == 0))  /*单挑*/
                       rl[b].ext = n;
             } else

            if (rl[a].type == ZC) { /* ZC*/
                if (rl[b].type == FZ || rl[b].type == NJ)  rl[a].ext++;
            }  else

            if (rl[a].type == FZ) { /* FZ */
                if (rl[b].type == ZC || rl[b].type == NJ)  rl[a].ext++;
                if (rl[b].type == ZG) rl[a].ext += 2;
            } else

            if (rl[a].type == NJ) { /* NJ */
            }
            rl[b].alive = 0;
            alive[rl[b].type]--;
        }
        for (; i < m; i++) scanf("%d %d", &a, &b);
        gets(buf);
        gets(buf);
        if (alive[ZG] == 0) { /* ZG is dead */
            if (alive[NJ] == 1 && alive[ZC] == 0 && alive[FZ] == 0) { /* only NJ alive */
                for (j = 0; j < n; j++) if (rl[j].type == NJ && rl[j].alive) break;
                rl[j].score = 4 + n*2 ;
                for (i = 0; i < n; i++) if (i != j) {
                    if (rl[i].type == ZG) rl[i].score = 1;
                    else rl[i].score = 0;
                }
            }
            else { /* FZ win */
                for (i = 0; i < n; i++) {
                    if (rl[i].type == FZ) rl[i].score = alive[FZ]*3 + rl[i].ext;
                    else if (rl[i].type == NJ && rl[i].alive) rl[i].score = 1;
                    else rl[i].score = 0;
                }
            }
        }
        else { /* ZG and ZC win */
            for (i = 0; i < n; i++) {
                if (rl[i].type == ZG)  rl[i].score = 4 + alive[ZC]*2 + rl[i].ext;
                else if (rl[i].type == ZC)  rl[i].score = 5 + alive[ZC] + rl[i].ext;
                else if (rl[i].type == NJ) rl[i].score = rl[i].ext;
                else rl[i].score = 0;
            }
        }
        for (i = 0; i < n-1; i++) printf("%d ", rl[i].score);
        printf("%d\n", rl[i].score);
    }
    return 0;
}
