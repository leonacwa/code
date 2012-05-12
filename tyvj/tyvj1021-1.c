//http://www.tyvj.cn:8080/Problem_Show.asp?id=1021
#include <stdio.h>

long long int x[10000];
int n;

void mysort(long long int a[], int l, int r)
{
     if (l>=r)
         return;
         
     long long int mid, x;
     int i, j;
     mid = a[l+(r-l)/2];
     i = l; j = r;
     while (i <= j)
     {
           while (i<=j && a[i] < mid)
               i++;
           while (i<=j && mid < a[j])
               j--;
           if (i<=j)
           {
               x = a[i];
               a[i] = a[j];
               a[j] = x;
               i++;
               j--;
           }
     }
     mysort(a, l, j);
     mysort(a, i, r);
     
}

int main()
{
    int i;
    long long int ans = 0;
    
    scanf("%d", &n);
    
    for (i = 0; i < n; i++)
        scanf("%ld", &x[i]);
    
    mysort(x, 0, n-1);
    
   // for (i = 0; i< n; i++) printf("%d  ", x[i]); putchar('\n');
    for ( i = 0; i < n-1; i++)
        ans += (i+1)*(n-i-1)*(x[i+1]-x[i]);
    ans*=2;
    //putchar('\n');
    printf("%ld", ans);
    
    //scanf("%d", &i);
    return 0;
}
