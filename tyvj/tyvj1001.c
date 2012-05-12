// http://www.tyvj.cn:8080/Problem_Show.asp?id=1001
#include <stdio.h>
#include <math.h>

int a[10000];
int n, k;

int cmp(int a, int b) { return a-b;}

void mysort(int a[], int l, int r)  //  注意自己写的快排的错误方式 
{
     if (l>=r)
         return;

     int mid, x, i, j;
     mid = a[l+(r-l)/2];
     i = l; j = r;
     while ( i <= j)  // 天煞的，快排写错了 
     {
         while (i<=j && a[i] < mid)
             i++;
         while (i<=j && mid < a[j])
             j--;
         if (i <= j)
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

int isprime(int n)
{
    if (n < 2)
        return 0;
    int r = (int)sqrt(n);
    int i;
    for (i = 2; i <= r; i++)
    {
          if (n % i == 0)
              return 0;
    }
    return 1;
}
int main()
{
    int i,  m;
    
    scanf("%d %d", &n,  &k);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
   
    mysort(a, 0, n-1);
    
    //qsort(a, n*sizeof(int), sizeof(int), cmp);
    
    m = a[n-k] - a[k-1];
    printf("%s\n%d\n", isprime(m)==1?"YES":"NO", m);
        
    scanf("%s", &a); // 记得把Debug信息去掉 
    return 0;
}
