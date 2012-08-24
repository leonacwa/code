/*The Frog's Games*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN (500000+1)

int a[MAXN];
int l, n, m;

int test(int jmp)
{
    int i, cm = m, x = 0;
    for (i = 1; i < n && cm > 0; i++) {
        if (a[i] - x > jmp) {
            if (a[i-1] - x <= jmp) {
                cm--;
                x = a[i-1];
            }
            else {
                return 0;
            }
        }
    }
    if (cm > 0 && a[n-1] - x <= jmp) return 1;
    return 0;
}

int main()
{
    int i, left, right, mid;
    while (~scanf("%d %d %d", &l, &n, &m)) {
        for (i = 1; i <= n; i++) scanf("%d", &a[i]);
        a[0] = 0;
        a[++n] = l;
        n++;
        sort(a, a+n);
        left = 0;
        right = l;
        while (left < right) {
            mid = (left + right) >> 1;
            if (test(mid))  right = mid;
            else left = mid+1;
        }
        printf("%d\n", left);
    }
    return 0;
}
