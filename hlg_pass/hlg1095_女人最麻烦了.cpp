#include <stdio.h>

#include <iostream>
#include <algorithm>
using namespace std;

struct Man{
    int acm, monney, rp;
};

bool cmp(const Man &a, const Man &b)
{
    if (a.acm != b.acm)
        return a.acm > b.acm;
    if (a.monney != b.monney)
        return a.monney > b.monney;
    return a.rp > b.rp;
}

int n;
Man m[1024];

int main()
{
    int i;
    while ( 1 == scanf("%d", &n)){
        for (i = 0; i < n; i++)
            scanf("%d %d %d", &m[i].acm, &m[i].monney, &m[i].rp);
        sort(m, m+n, cmp);
        for (i = 0; i < n; i++)
            printf("%d %d %d\n", m[i].acm, m[i].monney, m[i].rp);
    }
    return 0;
}
