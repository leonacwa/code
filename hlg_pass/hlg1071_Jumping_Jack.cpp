/*** // Jumping Jack */
#include <stdio.h>
#include <string.h>

int main()
{
    int s[2]={0}, p[2]={0}, ss[2]={0};
    int x, i, ii, ans;
    while (1 == scanf("%d", &x)){
        if (x == 0){
            printf("0\n");
            continue;
        }
        if (x < 0)
            x = -x;
        i = 1;
        p[1] = 1;
        s[1] = 1;
        ss[1] = 1;
        for ( ; ; ){
            ii = 1 - i;
            p[ii] = p[i] + 2;
            s[ii] = s[i] + p[i]*2 + 1;
            ss[ii] = ss[i] + 1 + 1;
            if (s[ii] > x)
                break;
            i = ii;
        }
        if (s[i] == x)
            printf("%d\n", ss[i]);
        else if (s[i] < x){
            ans = ss[i];
            if (x <= s[i]+p[i])
                ans += ((x - s[i])%2) * 2;
            else
                ans += 2;
            if (x > s[i]+p[i] && x <= s[i]+p[i]*2)
                ans += ((x - s[i] - p[i])%2) * (-1);
            printf("%d\n", ans);
        }
      /*** /  else             printf("Error!\n"); */
    }
    return 0;
}
