/* zoj1151_word_reversal */
#include <stdio.h>
#include <string.h>

int main()
{
    char str[1024], t2[1024];
    int t, n, len, slen;

    scanf("%d\n", &t);
    while (t--){ /// 多个case
        scanf("%d\n", &n);
        while (n--){///每个case几行
            gets(str); ///读入一行
            len = 0;
            slen = strlen(str);
            for (int i = 0; i < slen; i++){ /// 循环判断读入的一行
                if (str[i] == ' '){ ///如果遇到空格
                    t2[len] = 0;
                    for (int j = strlen(t2)-1; j >= 0; j--)///反转输出
                        putchar(t2[j]);
                    putchar(' ');
                    len = 0;
                    continue;///下一个单词
                }
                t2[len++] = str[i];///存储单词
           }
           t2[len] = 0; /// 输出最后的一个单词
           for (int j = strlen(t2)-1; j >= 0; j--)
               putchar(t2[j]);
           putchar('\n');
        }
        if (t) ///相邻的case用换行间隔
            printf("\n");
    }
    return 0;
}
