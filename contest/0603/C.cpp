#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;
typedef long long llong;
int main()
{
    llong x, y, r;
    while (EOF != scanf("%lld%lld%lld", &x, &y, &r)) {
        if (x == 0 && y == 0 && r == 0) break;
        llong r2 = r * r;
        llong ans = 0;
        for (llong x = -r+1; x <= 0; ++x) {
            llong y2 = r2 - x * x;
            llong y = (llong)(sqrt(y2*1.0) + 1e-8);
            if (y * y < y2) {
                ++y;
            }
            ans += y + y;
        }
        for (llong x = 0; x < r; ++x) {
            llong y2 = r2 - x * x;
            llong y = (llong)(sqrt(y2*1.0) + 1e-8);
            if (y * y < y2) {
                ++y;
            }
            ans += y + y;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
