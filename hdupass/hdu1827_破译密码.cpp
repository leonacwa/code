// hdu1827 ∆∆“Î√‹¬Î http://acm.hdu.edu.cn/showproblem.php?pid=1287

#include <stdio.h>
#include <string.h>
int n;
char str[4096+1];
char ans[4096+1];

int main()
{
    int i;
    while (EOF != scanf("%d", &n) && n){
        for (int i = 0; i < n; i++){
            scanf("%d", &str[i]);
           // printf("%d ", str[i]);
        }
            
        str[n] = 0;
        for (char c = 'A'; c <= 'Z'; c++){
            for (i = 0; (ans[i] = str[i]^c) && ('A' <= ans[i]) && (ans[i] <= 'Z') && (i < n); ++i)
            ;
            
            if (i == n)
                break;
        }
        for (int i = 0; i < n; i++)
            printf("%c", ans[i]);
        
        printf("\n");
        n = 0;
    }
    
    return 0;
    
}
