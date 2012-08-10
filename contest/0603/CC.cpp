#include <stdio.h>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    long long x, y, r, count;
    while(scanf("%lld%lld%lld", &x, &y, &r) != EOF)
    {
        if(x == 0 && y == 0 && r == 0) break;
        count = 0;
        for(long long i = r-1; i >= 0; --i)
        {
            long long  k = (long long)(sqrt(r*r - i*i + 0.0) + 1e-8);
            if(k*k < r*r - i*i) count += k + 1;
            else count += k;
        }

        count *= 4;
        printf("%lld\n", count);

    }//while
    return 0;
}
