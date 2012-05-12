//http://acm.hrbeu.edu.cn/index.php?act=problem&id=1003&cid=17
//Ä¾°ôÈý½ÇÐÎ 
#include <iostream>
using namespace std;

int n;
int stk[100];

inline bool IsR(int a, int b, int c)
{return a*a + b*b == c*c;}

int main()
{
    int i, j, k;
    double max, t;
    while (scanf("%d", &n) != EOF)
    {
        for (i = 0; i < n; i++)
            scanf("%d", stk + i);
        max = -100;
        for (i = n - 1; i > 1; i--)
        for (j = i - 1; j > 0; j-- )
        for (k = j - 1; k >= 0; k--)
        if (IsR(stk[k], stk[j], stk[i]))
        {
            t = double(stk[k]*stk[j]) / 2;
            if (max < t)
                max = t;
        }
        if (max > 0)
            printf("%0.3f\n", max);
        else
            printf("My Good!\n");
    }
    return 0;
}
