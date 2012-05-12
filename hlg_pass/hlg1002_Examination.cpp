#include <iostream>
#include <algorithm>
using namespace std;

int a[1000+56];
int n, m, k;

int main()
{
    int i, cnt = 0;
    while (3 == scanf("%d %d %d", &n, &m, &k)){
        for (i = n*m-1; i >= 0; i--)
            scanf("%d", a+i);
        sort(a, a+n*m);
        printf("Scenario #%d\n%d\n\n", ++cnt, a[n*m-k]);
    }
    return 0;
}