/* 二分法快速判断m个点在由n个点构成的凸多边形内，时间复杂度O(m*logn) 
*/

typedef long long llong;
const int MAXN = 100000 + 100;
struct Point {
    llong x, y;
} pt[MAXN];

llong cross(const Point &A, const Point &B, const Point &C) {
    return (A.x - C.x) * (B.y - C.y) - (A.y - C.y) * (B.x - C.x);
}
bool bin(int &l, int &r, const Point &p)
{
    while (l+1 < r) {
        int m = (l + r) >> 1;
        if (cross(p, pt[m], pt[0]) <= 0) r = m;
        } else l = m;
    }
    if (cross(pt[l], p, pt[0]) <= 0 && cross(p, pt[r], pt[0]) <= 0) {
        return true;
    }
    return false;
}
int main()
{
    int n, m;
    while (EOF != scanf("%d", &n)) {
        for (int i = 0; i < n; ++i) {
            scanf("%lld %lld", &pt[i].x, &pt[i].y);
        }
        scanf("%d", &m);
        bool ans = true;
        for (int i = 0; i < m; ++i) {
            Point p;
            scanf("%lld %lld", &p.x, &p.y);
            if (!ans) continue;
            int l = 1, r = n - 1;
            if (bin(l, r, p)) {
                if (l == 1 && cross(pt[l], p, pt[0]) == 0) {
                    ans = false;
                } else if (r == n - 1 && cross(p, pt[r], pt[0]) == 0) {
                    ans = false;
                } else if(cross(pt[l], p, pt[r]) <= 0) {
                    ans = false;
                }
            } else {
                ans = false;
            }
        }
        puts(ans ? "YES" : "NO");
    }
    return 0;
}