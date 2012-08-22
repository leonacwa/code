/** Catch That Cow 
http://acm.hrbust.edu.cn/showproblem.php?problemid=1012
*/
#include <stdio.h>
#include <string.h>

#define MAXN 100000
struct Pos{
    int p, s;
} pos[MAXN*4];

char vis[MAXN+1];

int n, k;

int bfs(int n, int k)
{
    if (n == k)
        return 0;
    int h, t, j;
    struct Pos pt[3];
    memset(vis, 0, sizeof(char)*(MAXN+1));
    h = 0;
    t = 0;
    pos[h].p = n;
    pos[h].s = 0;
    vis[n] = 1;
    while (pos[h].p != k){
        pt[0].p = pos[h].p - 1;
        pt[1].p = pos[h].p + 1;
        pt[2].p = pos[h].p * 2;
        pt[0].s = pt[1].s = pt[2].s = pos[h].s + 1;
        h++;
        for (j = 0; j < 3; j++){
            if (pt[j].p < 0 || pt[j].p > MAXN) /** 边界没有考虑到啊，老是WA */
                continue;
            if ((char)0 == vis[pt[j].p]){
                t++;
                pos[t] = pt[j];
                vis[pt[j].p] = 1;
            }
        }
    }
    return pos[h].s;
}
int main()
{
    while (2 == scanf("%d %d", &n, &k)){
        printf("%d\n", bfs(n, k));
    }
    return 0;
}
