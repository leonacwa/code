/// 店长终极推荐  http://acm.hrbust.edu.cn/showproblem.php?problemid=1109
#include <stdio.h>
#include <string.h>

int main()
{
    char str_max[3], strnow[3], str[256];
    int Max, cnt, i, j, k, ls, tt, flag = 0;
    while (1 == scanf("%d\n", &tt) && tt) {
        while (tt--) {
            gets(str);
            ls = strlen(str);
            Max = 0;
            str_max[0] = 0;
            for (i = 0; i < ls-1; i++) {
                strnow[0] = str[i];
                strnow[1] = str[i+1];
                strnow[2] = 0;
                cnt = 1;
                for (j = i+1; j < ls-1; j++) {
                    if (strnow[0] == str[j] && strnow[1] == str[j+1])
                        cnt++;
                }
                if (Max < cnt) {
                    Max = cnt;
                    strcpy(str_max, strnow);
                }
                else if (Max == cnt){
                    if (str_max[0] && strcmp(strnow, str_max) < 0)
                        strcpy(str_max, strnow);
                }
            }
            printf("%s\n", str_max);
        }
        printf("\n");
    }
    return 0;
}
