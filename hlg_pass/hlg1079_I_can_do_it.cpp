// I can do it
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
#include <iostream>
#include <algorithm>
using namespace std;
*/
struct AB{
    int a, b;
};
/*
inline bool cpp_cmp_a(const AB &a, const AB &b)
{
    return a.a < b.a;
}
*/
int c_cmp_a(const void*a, const void*b)
{
    return ((const AB*)a)->a - ((const AB*)b)->a;
}
struct AB ab[100000];

int main()
{
    int i, ans, max_b, t, n;
    int tt, cnt = 0;
    
    scanf("%d", &tt);
    while (tt--){
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d %d", &ab[i].a, &ab[i].b);
        
        //sort(ab, ab+n, cpp_cmp_a);
        qsort(ab, n, sizeof(ab[0]), c_cmp_a);
        max_b = ab[n-1].b;
        ans = max_b + ab[n-2].a;
        for (i = n-2; i > 0; i--){
            if (max_b < ab[i].b)
                max_b = ab[i].b;
            t = ab[i-1].a + max_b;
            if (t < ans)
                ans = t;
        }
        t = ab[n-i].a + max_b;
        if (t < ans)
            ans = t;
        printf("Case %d: %d\n", ++cnt, ans);
    }
    return 0;
}
