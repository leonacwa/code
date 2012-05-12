//Chocolate Auction
#include <stdio.h>
#include <string.h>

#define MAXN (10000000 + 128)

int fa[MAXN];

int find(int x)
{
    if (x == fa[x])
        return x;
    
    int fx = x;
    int px;
    while (fx != fa[fx])
        fx = fa[fx];
    while (x != fx){
        px = fa[x];
        fa[x] = fx;
        x = px;
    }
    return fx;
}
void _union(int x, int y) /// x -> y
{
    int fx = find(x);
    int fy = find(y);
    fa[fx] = fy;
}
int main()
{
    int tt, N, M;
    int i, j, aa, res, a, b;
    
    scanf("%d", &tt);
    while (tt--){
        scanf("%d %d", &N, &M);
        for (i = 0; i <= N+128; i++)
            fa[i] = i;
        for (i = 0; i < M; i++){
            scanf("%d %d", &a, &b);
            res = 0;
            for (aa = a; aa <= b; aa++){
                aa = find(aa);
                if (aa > b)
                    break;
                res++;
                _union(aa, aa+1);
            }
            printf("%d\n", res);
        }
    }
    return 0;
}

