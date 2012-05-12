/// 1013
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN (100*100+1)

struct Result{
    int x, s;
} rs[MAXN];
int rc;
/* // for qsort
int c_cmp(const void*a, const void*b)
{
    return ((Result*)a)->x -  ((Result*)b)->x;
}
*/
bool cpp_cmp(const Result&a, const Result&b)
{
    return a.x < b.x;
}
int find(int x)
{
    int l = 0, r = rc-1, mid;
    while (l < r){
        mid = (l+r) / 2;
        if (rs[mid].x == x)
            return mid;
        else if (rs[mid].x < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    mid = (l+r) / 2;
    if (rs[mid].x == x)
        return mid;
    return -1;
}
int main()
{
    int x0, x1, x2, t0, t1, t2, i, j, ans, pos;
    int a[5];
    while ( 5 == scanf("%d %d %d %d %d", a, a+1, a+2, a+3, a+4)){
        rc = 0;
        for (x0 = -50; x0 <= 50; x0++) if (x0 != 0){
            t0 = a[0] * x0 * x0 * x0;
            for (x1 = -50; x1 <= 50; x1++) if (x1 != 0){
                t1 = t0 + a[1] * x1 * x1 * x1;
                rs[rc].x = t1;
                rs[rc++].s = 1;
            }
        }
        //qsort(rs, rc, sizeof(Result), cmp);
        sort(rs, rs+rc, cpp_cmp);
        j = 0;
        for (i = 0; i < rc; ){
            t0 = rs[i].x;
            t1 = 0;
            for ( ; i < rc && rs[i].x == t0; i++)
                t1++;
            rs[j].x = t0;
            rs[j++].s = t1;
        }
        rc = j;
        ans = 0;
        for (x0 = -50; x0 <= 50; x0++) if (x0 != 0){
            t0 = a[2] * x0 * x0 * x0;
            for (x1 = -50; x1 <= 50; x1++) if (x1 != 0){
                t1 = t0 + a[3] * x1 * x1 * x1;
                for (x2 = -50; x2 <= 50; x2++) if (x2 != 0){
                    t2 = t1 + a[4] * x2 * x2 *x2;
                    pos = find(t2);
                    if (pos != -1){
                        ans += rs[pos].s;
                    }
                }
                
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
