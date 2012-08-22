/**
向量(x,y)旋转a弧度后向量为(x*cosa - y*sina, x*sina + y*cosa)

缺少计算几何的知识，自己磨了挺久，主要原因是自己不在状态，老感觉不得其法，浪费了大把的时间。
还是知识的不够啊，还得再学习计算几何的知识啊
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 10000 + 10;
double PI;
struct Node {
    int a; // 记录的线段顺时针旋转多少度与Y轴重合
    double x, y;
} T[MAXN<<2];
int len[MAXN];

void change(int rt, int a)
{
    T[rt].a = (a + T[rt].a) % 360;
    double x = T[rt].x, y = T[rt].y;
    double d = a * PI / 180.0;
    T[rt].x = x * cos(d) - y * sin(d);
    T[rt].y = x * sin(d) + y * cos(d);
}

void PushUp(int rt)
{
    T[rt].x = T[rt<<1].x + T[rt<<1|1].x;
    T[rt].y = T[rt<<1].y + T[rt<<1|1].y;
}

void PushDown(int rt)
{
    if (T[rt].a) {
        change(rt<<1, T[rt].a);
        change(rt<<1|1, T[rt].a);
        T[rt].a = 0;
    }
}

void make_tree(int rt, int L, int R)
{
    T[rt].x = 0;
    T[rt].a = 0;
    if (L == R) {
        T[rt].y = len[L];
        return;
    }
    int m = (L + R) >> 1;
    make_tree(rt<<1, L, m);
    make_tree(rt<<1|1, m+1, R);
    PushUp(rt);
}

void update(int rt, int L, int R, int l, int r, int a)
{
    if (l <= L && R <= r) {
        change(rt, a);
        return;
    }
    if (L == R) return;
    int m = (L + R) >> 1;
    PushDown(rt);
    if (l <= m) update(rt<<1, L, m, l, r, a);
    if (m < r) update(rt<<1|1, m+1, R, l, r, a);
    PushUp(rt);
}

int query(int rt, int L, int R, int p)
{
    if (L == p && p == R) {
        return T[rt].a;
    }
    PushDown(rt);
    int m = (L + R) >> 1;
    if (p <= m) return query(rt<<1, L, m, p);
    return query(rt<<1|1, m+1, R, p);
}

int main()
{
    PI = acos(-1.0);
    int n, c;
    bool flag = false;
    while (EOF != scanf("%d%d", &n, &c)) {
        for (int i = 1; i <= n; ++i) scanf("%d", &len[i]);
        make_tree(1, 1, n);
        for (int i = 1; i <= c; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            int a1 = query(1, 1, n, x);
            int a2 = query(1, 1, n, x+1);
            update(1, 1, n, x+1, n, (360 + 180 - a2 + a1 + y) % 360);
            printf("%.2lf %.2lf\n", T[1].x, T[1].y);
        }
        if (flag) puts("");
        flag = true;
    }
    return 0;
}
