/*Graph*/
#include <stdio.h>
#include <string.h>
#define MAXN 101
#define INF 0x3fffffff

int map[MAXN][MAXN];
bool del[MAXN][MAXN];
int n;

int main()
{
    int cs, tt;
    int cnt, i, j, k, tmp, ret;
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        scanf("%d", &n);
        cnt = 0;
        for (i = 1; i <= n; i++)  {
            for (j = 1; j <= n; j++ ) {
                scanf("%d", &map[i][j]);
                del[i][j] = false;
                if (map[i][j]) cnt++;
            }
        }
        for (k = 1; k <= n; k++) {
            for (i = 1; i <= n; i++) if (i != k){
                for (j = 1; j <= n; j++) if (j != k && j != i && !del[i][j]) {
                    if (map[i][j] == map[i][k] + map[k][j]) {
                        del[i][j] = true;
                        cnt--;
                    }
                    else if (map[i][j] > map[i][k] + map[k][j]) {
                        cnt = 0;
                        goto Ans;
                    }
                }
            }
        }
        Ans:
        if (cnt > 0) printf("Case %d: %d\n", cs, cnt);
        else printf("Case %d: impossible\n", cs);
    }
    return 0;
}
