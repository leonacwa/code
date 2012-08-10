#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <climits>
using namespace std;

double p[15][105];

int main()
{
    int n, m, nm;
    while (EOF != scanf("%d%d", &n, &m)) {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%lf", &p[j][i]);
            }
        }
        for (int j = 0; j < m; ++j) sort(p[j], p[j] + n);
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            double pa = 1;
            for (int j = 0; j < m; ++j) pa *= p[j][i];
            sum += pa;
        }
        printf("%.4lf\n", sum);
    }
    return 0;
}
