#include <stdio.h>

int main()
{
    int n, num[1000]={0};
    int i, tot, t, tt;
    
    scanf("%d", &n);
    
    tot = 0;
    tt = n;
    if ( n )
    while ( tt != 1 )
    {
        t = tt % -2;
        tt = tt / -2;
        if (t < 0)
        {
            t += 2;
            tt++;
        }
        num[tot++] = t;
    }
    num[tot] = tt; //  我在这里把 = 写成 == 
    for (i = tot; i>=0; i--)
        putchar(num[i]+'0');
    
    putchar('\n');
    system("pause");
    return 0;
}
