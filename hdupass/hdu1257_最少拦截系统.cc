/**
最少拦截系统
http://acm.hdu.edu.cn/showproblem.php?pid=1257
*/

#include <stdio.h>
#include <string.h>

#define MAXN (4096)
int h[MAXN];
int f[MAXN];
int n, tot;

int main()
{
    int i, k, j;
    
    while (1 == scanf("%d", &n)){
        for (i = 0; i < n; i++)
            scanf("%d", h+i);
        tot = 1;
        f[0] = h[0];
        
        for (i = 1; i < n; i++){
            k = -1;
            for (j = 0; j < tot; j++){
                if (h[i] <= f[j]){
                    k = j;
                    break;
                }
            }
            if (k == -1){
                f[tot++] = h[i];
                continue;
            }
            for (; j < tot; j++){
                if (h[i] <= f[j] && f[j] < f[k]){
                    k = j;
                }
            }
            f[k] = h[i];
        }
        
        printf("%d\n", tot);
    }
    return 0;
}
