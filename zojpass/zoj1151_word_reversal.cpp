/* zoj1151_word_reversal */
#include <stdio.h>
#include <string.h>

int main()
{
    char str[1024], t2[1024];
    int t, n, len, slen;

    scanf("%d\n", &t);
    while (t--){ /// ���case
        scanf("%d\n", &n);
        while (n--){///ÿ��case����
            gets(str); ///����һ��
            len = 0;
            slen = strlen(str);
            for (int i = 0; i < slen; i++){ /// ѭ���ж϶����һ��
                if (str[i] == ' '){ ///��������ո�
                    t2[len] = 0;
                    for (int j = strlen(t2)-1; j >= 0; j--)///��ת���
                        putchar(t2[j]);
                    putchar(' ');
                    len = 0;
                    continue;///��һ������
                }
                t2[len++] = str[i];///�洢����
           }
           t2[len] = 0; /// �������һ������
           for (int j = strlen(t2)-1; j >= 0; j--)
               putchar(t2[j]);
           putchar('\n');
        }
        if (t) ///���ڵ�case�û��м��
            printf("\n");
    }
    return 0;
}
