/** poj1016 Numbers That Count */
#include <stdio.h>
#include <string.h>
char str[17][128];
void inv(const char*from, char*to)
{
    int l=strlen(from), i;
    int ns[10]={0};
    for (i = 0; i < l; i++) {
        ns[from[i]-'0']++;
    }
    l = 0;
    for (i = 0; i < 10; i++) {
        if (ns[i]) {
            if (ns[i] >= 10) {
                to[l++] = '0' + ns[i] / 10;
            }
            to[l++] = '0' + ns[i] % 10;
            to[l++] = '0' + i;
        }
    }
    to[l] = 0;
}
int main()
{
    int i, k, ff;
    while (gets(str[0])){
        //puts(str[0]);
        if (0 == strcmp(str[0], "-1")) {
            break;
        }
        inv(str[0], str[1]);
        if (0 == strcmp(str[0], str[1])) {
            printf("%s is self-inventorying\n", str[0]);
            continue;
        }
        ff = 0;
        for (i = 1; i <= 15; i++) {
            inv(str[i], str[i+1]);// puts(str[i]);
            if (0 == strcmp(str[i], str[i+1])) {
                printf("%s is self-inventorying after %d steps\n", str[0], i);
                ff = 1;
                break;
            }
        }
        for (i = 0;i <= 13 && !ff; i++) {
            for (k = 2; i+k <= 15; k++) {
                if (0 == strcmp(str[i], str[i+k])) {
                    i = 999;
                    ff = 1;
                    printf("%s enters an inventory loop of length %d\n", str[0], k);
                    break;
                }
            }
        }
        if (!ff) {
            printf("%s can not be classified after 15 iterations\n", str[0]);
        }
    }
    return 0;
}
