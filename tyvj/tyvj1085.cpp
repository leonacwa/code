// http://www.tyvj.cn:8080/Problem_Show.asp?id=1085
#include <stdio.h>
#include <string.h> 

int g_n, g_k, ans;
int h[10], a[10], u[10];

int abs(int n)
{
    return n<0?-n:n; 
}

void find(int k)
{
     int j;
     if (k == g_n && abs(a[k-1]-a[0])<=g_k)
     {
           ans++;
           return;
     }
     for (j = 0; j < g_n; j++)
     if(u[j] == 0 && abs(a[k-1]-h[j])<=g_k)
     {
         u[j] = 1;
         a[k] = h[j];
         find(k+1);
         u[j] = 0;
     }
}

int main()
{
    int i;
    ans = 0;
    scanf("%d %d", &g_n, &g_k);
    for (i = 0; i < g_n; i++)
        scanf("%d", &h[i]);
   
    memset(u, 0, sizeof(int)*10);
   
    a[0] = h[0];
    u[0] = 1;
    find(1);
   
    printf("%d\n", ans);
  // scanf("%c");
    return 0; 
}
