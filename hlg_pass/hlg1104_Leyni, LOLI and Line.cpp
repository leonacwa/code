/// Leyni, LOLI and Line  http://acm.hrbust.edu.cn/showproblem.php?problemid=1104
/** 
   根据两点和 ax + by = c， 求得
   (y2-y1)x + (x1-x2)y = x1*y2 - x2*y1
   线性代数很有用啊
*/
#include <stdio.h>
#include <string.h> 
#define zero(x) (((x)<0?-(x):(x)) < 1e-8)
int i_abs(int x){return x<0?-x:x;}
int i_min(int a, int b){return a<b?a:b;}
int i_max(int a, int b){return a>b?a:b;}
double d_abs(double x){return x<0?-x:x;}
double d_min(double a, double b){return a<b?a:b;}
double d_max(double a, double b){return a>b?a:b;}

int main()
{
    int tt, i;
    int x[4], y[4], a[2], b[2], c[2];
    char flag;
    double d, x5, y5;
    scanf("%d", &tt);
    while (tt--){
        for (i = 0; i < 4; i++)
            scanf("%d %d", x+i, y+i);
        a[0] = y[1] - y[0];
        b[0] = x[0] - x[1];
        c[0] = x[0]*y[1] - x[1]*y[0];
        a[1] = y[3] - y[2];
        b[1] = x[2] - x[3];
        c[1] = x[2]*y[3] - x[3]*y[2];
        flag = 'N';
        if ((a[0] == 0 && a[1] == 0) || (b[0] == 0 && b[1] == 0)){
            if ( ((a[0] == 0 && d_abs(1.0*c[0]/b[0] - 1.0*c[1]/b[1]) < 1e-8)
                ||(b[0] == 0 && d_abs(1.0*c[0]/a[0] - 1.0*c[1]/a[1]) < 1e-8))
              /*&& d_min(x[0],x[1]) == d_min(x[2],x[3])
              && d_min(y[0],y[1]) == d_min(y[2],y[3])
              && d_max(x[0],x[1]) == d_max(x[2],x[3])
              && d_max(y[0],y[1]) == d_max(y[2],y[3])*/ )
                flag = 'L';
            else
                flag = 'N';
        }
        else if (b[0] && b[1] && d_abs(1.0*a[0]/b[0] - 1.0*a[1]/b[1]) < 1e-8){
            if (  d_abs(1.0*c[0]/b[0] - 1.0*c[1]/b[1]) < 1e-8
              /*&& d_min(x[0],x[1]) == d_min(x[2],x[3])
              && d_min(y[0],y[1]) == d_min(y[2],y[3])
              && d_max(x[0],x[1]) == d_max(x[2],x[3])
              && d_max(y[0],y[1]) == d_max(y[2],y[3])*/ )
                flag = 'L';
            else
                flag = 'N';
        }
        else {
            d = a[0]*b[1] - a[1]*b[0];
            x5 = (c[0]*b[1] - c[1]*b[0]) / d;
            y5 = (a[0]*c[1] - a[1]*c[0]) / d;
            /*
            if ( d_min(x[0], x[1]) <= x5 && x5 <= d_max(x[0], x[1])
              && d_min(y[0], y[1]) <= y5 && y5 <= d_max(y[0], y[1])
              && d_min(x[2], x[3]) <= x5 && x5 <= d_max(x[2], x[3])
              && d_min(y[2], y[3]) <= y5 && y5 <= d_max(y[2], y[3])
                )
                flag = 'P';
            else
                flag = 'N';
                */
            flag = 'P';
        }
        if (flag == 'N')
            printf("NONE\n");
        else if (flag == 'L')
            printf("LINE\n");
        else if (flag == 'P')
            printf("POINT %.2f %.2f\n", x5, y5);
        else while (1) printf("ERROR %c\n", flag);
    }
    return 0;
}
