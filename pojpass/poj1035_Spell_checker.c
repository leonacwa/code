/* poj 1035 Spell checker */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS (100000+1)

typedef struct _Word{
    char str[24];
    int order;
}Word;
Word w[MAX_WORDS], cw[2], *dw[MAX_WORDS];
int ws, ds, order;

int my_word_cmp_sort(const void *a, const void *b)
{
    return strcmp(((Word*)a)->str, ((Word*)b)->str);
}
int word_order_cmp(const void *a, const void *b)
{
    return (*((Word**)a))->order - (*((Word**)b))->order;
}
int find(const char *s)
{
    int left = 0, right = ws-1, mid, ret;
    while (left < right-1) {
        mid = left + (right - left) / 2;
        ret = strcmp(s, w[mid].str);
        if ( ret < 0) {
            right = mid;
        }
        else if (ret > 0) {
            left = mid;
        }
        else {
            return mid;
        }
    }
    if (0 == strcmp(s, w[left].str)) {
        return left;
    }
    if (0 == strcmp(s, w[right].str)) {
        return right;
    }
    return -1;
}

char del_char(char *s, int p) {
    char t = s[p];
    for (; s[p]; p++) {
        s[p] = s[p+1];
    }
    return t;
}
char ins_char(char *s, char c, int p)
{
    int ls = strlen(s);
    for (; p <= ls; ls--) {
        s[ls+1] = s[ls];
    }
    s[p] = c;
    return c;
}
char rep_char(char *s, char c, int p)
{
    char t = s[p];
    s[p] = c;
    return t;
}
int main()
{
    int i, ret, lw;
    char c;

    ws = 0;
    order = 0;
    while (gets(w[ws].str) && w[ws].str[0] != '#') {
        w[ws++].order = ++order;
    }
    qsort(w, ws, sizeof(Word), my_word_cmp_sort);
    while (gets(cw[0].str) && cw[0].str[0] != '#') {
        if (-1 != find(cw[0].str)) {
            printf("%s is correct\n", cw[0].str);
        }
        else {
            printf("%s:", cw[0].str);
            lw = strlen(cw[0].str);
            ds = 0;
            for (i = 0; i <= lw; i++) {
                if (cw[0].str[i]) {
                    cw[1] = cw[0]; /// delete
                    del_char(cw[1].str, i);
                    ret = find(cw[1].str);
                    if (-1 != ret) {
                        dw[ds++] = &w[ret];
                    }
                }
                for (c = 'a'; c <= 'z'; c++) {
                    cw[1] = cw[0];  /// insert
                    ins_char(cw[1].str, c, i);
                    ret = find(cw[1].str);
                    if (-1 != ret) {
                        dw[ds++] = &w[ret];
                    }
                    if (cw[0].str[i]) {
                        cw[1] = cw[0];  /// replace
                        rep_char(cw[1].str, c, i);
                        ret = find(cw[1].str);
                        if (-1 != ret) {
                            dw[ds++] = &w[ret];
                        }
                    }
                }
            }
            qsort(dw, ds, sizeof(Word*), word_order_cmp);
            if (ds > 0) order = dw[0]->order - 1;
            for (i = 0; i < ds; i++) {
                if (order != dw[i]->order) {
                    printf(" %s", dw[i]->str);
                    order = dw[i]->order;
                }
            }
            printf("\n");
        }
    }
    return 0;
}
