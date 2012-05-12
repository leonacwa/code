/* poj 1703 Find them, Catch them */
/// 1 different, 0 same
#include <stdio.h>
#include <string.h>
#define MAXN (100000+1)

int f[MAXN], d[MAXN];

int f_set(int x)
{
    int ft;
    if (f[x] == x) {
        return x;
    }
    ft = f_set(f[x]);
    d[x] = (d[x] + d[f[x]]) % 2;
    f[x] = ft;
    return ft;
}
void u_set(int a, int b)
{
    int fa = f_set(a);
    int fb = f_set(b);
    if (fa == fb) {
        return;
    }
    d[fa] = (1 + d[b] - d[a] + 2) % 2;
    f[fa] = fb;
}
int main()
{
    int tt, n, m, a, b, i;
    char c;

    scanf("%d", &tt);
    while (tt--) {
        scanf("%d %d\n", &n, &m);
        for (i = 0; i <= n; i++) {
            f[i] = i;
            d[i] = 0;
        }
        for (i = 0; i < m; i++) {
            scanf("%c %d %d\n", &c, &a, &b);
            if (c == 'A') {
                if (f_set(a) != f_set(b)) {
                    puts("Not sure yet.");
                }
                else if (d[a]%2 == d[b]%2){
                    puts("In the same gang.");
                }
                else {
                    puts("In different gangs.");
                }
            }
            else if (c == 'D') {
                u_set(a, b);
            }
        }
    }
    return 0;
}
