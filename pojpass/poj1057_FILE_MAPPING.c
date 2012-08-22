/* poj 1057 FILE MAPPING */
/// 递归处理目录,目录按出现顺序，文件按文件名字典序
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10000
#define MAX_FILE_NAME_LENGTH 256
typedef struct _FileNme{
    char str[MAX_FILE_NAME_LENGTH];
}FileName;
FileName fnm[MAXN];
int fns;
int file_name_cmp(const void *a, const void *b)
{
    return strcmp((*(FileName**)a)->str, (*(FileName**)b)->str);
}
void deal_dir(char *b)
{
    char str[MAX_FILE_NAME_LENGTH], bb[1000];
    FileName *fls[MAXN];
    int i, fs = 0;
    strcpy(bb, b);
    strcat(bb, "|     ");
    while (gets(str) && str[0] != ']' && str[0] != '*') {
        if (str[0] == 'd') {
            printf("%s%s\n", bb, str);
            deal_dir(bb);
        }
        else if (str[0] == 'f'){
            fls[fs] = &fnm[fns++];
            strcpy(fls[fs]->str, str);
            fs++;
        }
    }
    qsort(fls, fs, sizeof(FileName*), file_name_cmp);
    for (i = 0; i < fs; i++) {
        printf("%s%s\n", b, fls[i]->str);
    }
    fns -= fs;
}
int main()
{
    int x = 0;
    char c = '#';
    while ((c=getc(stdin)) && c != '#') {
        ungetc(c, stdin);
        printf("DATA SET %d:\nROOT\n", ++x);
        deal_dir("");
        printf("\n");
    }
    return 0;
}
