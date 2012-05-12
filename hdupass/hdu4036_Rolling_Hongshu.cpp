/*Rolling Hongshu*/
#include <stdio.h>
#include <math.h>
#define MAXN (1000+10)
#define G 20
#define eps 1e-8

struct Moutain {
    double x, h;
};
Moutain mou[MAXN];

int main()
{
    int cs, tt;
    double ans, tmpv, h;
    int i, j, N, M;
    double w, x, v;
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        scanf("%d %d %d", &N, &M, &w);
        ans = 0;
        for (i = 0; i < N; i++) {
            scanf("%lf %lf", &mou[i].x, &mou[i].h);
            if (mou[i].h > mou[0].h) {
                tmpv = sqrt(2.0*G*(mou[i].h - mou[0].h));
                if (ans < tmpv) ans = tmpv;
            }
        }
        for (i = 0; i < M; i++) {
            scanf("%lf %lf %lf", &x, &v, &w);
            x = mou[0].x + x;
            for (j = 0; j < N-1; j++) {
                if (mou[j].x <= x && x <= mou[j+1].x) {
                    h = 1.0*(mou[j+1].h - mou[j].h)*(x - mou[j].x) / (mou[j+1].x - mou[j].x) + mou[j].h;
                    break;
                }
            }
            tmpv = sqrt(v*v + 2.0*G*(h - mou[0].h)+eps);
            if (ans < tmpv)  ans = tmpv;
        }
        printf("Case %d: %.2lf\n", cs, ans);
    }
    return 0;
}
