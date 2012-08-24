/**
  B-numberµÄ´ò±í
*/
#include <stdio.h>
#include <string.h>

#define SEG 200000

int main()
{
    freopen("B-numbers_ans.txt", "w", stdout);
    int i, cnt, d, count;
    int m, mm = 1000000000;
    cnt = 0;
    count = 0;
    m = SEG + 131;
    for (i = 13; i <= m; i++){
        for (d = i; d && d%100 != 13; d /= 10)
        ;
        if (d && i%13 == 0){
            cnt++;
        }
        printf("%d:%d\n", i, cnt);
    }
    return 0;
}
