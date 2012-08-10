#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int m, g, z, s, e;
    while (EOF != scanf("%d%d%d%d%d", &m, &g, &z, &s, &e)) {
        if (!(m | g | z | s | e)) break;
        int nz = m / 100, ns = min(m / 125, g / 50), ans = 0;
        for (int i = 0; i <= nz; ++i) {
            for (int j = 0; j <= ns; ++j) {
                int rm = m - 100 * i - 125 * j, rg = g - 50 * j;
                if (rm <= 0 || g <= 0) break;
                int ne = min(rm / 50, rg / 100);
                int t = i * z + j * s + ne * e;
                if (ans < t) ans = t;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
