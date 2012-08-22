/* poj 1051 P,MTHBGWB */
#include <stdio.h>
#include <string.h>
#define MAXN 128
#define underscore '_'
#define period '.'
#define comma ','
#define question_mark '?'
#define index_underscore 26
#define index_period 27
#define index_comma 28
#define index_question_mark 29

char morse_code[26+4][5] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",/*A..G*/
    "....", "..", ".---", "-.-", ".-..", "--", "-.", /*H..N*/
    "---", ".--.", "--.-", ".-.", "...", "-", "..-", /*O..U*/
    "...-", ".--", "-..-", "-.--", "--..", /*V..Z*/
    "..--", "---.", ".-.-", "----" /*underscore period comma question mark*/
};

const char* code(char c)
{
    if (c == underscore) {
        return morse_code[index_underscore];
    }
    else if (c == period) {
        return morse_code[index_period];
    }
    else if (c == comma) {
        return morse_code[index_comma];
    }
    else if (c == question_mark) {
        return morse_code[index_question_mark];
    }
    return morse_code[c - 'A'];
}
char decode(const char*str)
{
    int i;
    for (i = 0; i < 26; i++) {
        if (0 == strcmp(str, morse_code[i])) {
            return (char)(i+'A');
        }
    }
    if (0 == strcmp(str, morse_code[index_underscore])) {
        return underscore;
    }
    if (0 == strcmp(str, morse_code[index_period])) {
        return period;
    }
    if (0 == strcmp(str, morse_code[index_comma])) {
        return comma;
    }
    if (0 == strcmp(str, morse_code[index_question_mark])) {
        return question_mark;
    }
    return -1;
}

int main()
{
    int i, j, x, lm, ml, la;
    char c;
    const char *s;
    char ms[MAXN], mlen[MAXN], mc[MAXN*5], ans[MAXN];
    scanf("%d\n", &x);
    for (i = 1; i <= x; i++) {
        gets(ms);
        mc[0] = 0;
        ml = 0;
        for (j = 0; ms[j]; j++) {
            s = code(ms[j]);
            mlen[ml++] = strlen(s);
            strcat(mc, s);
        }
        ans[0] = 0;
        lm = 0;
        la = 0;
        for (j = ml-1; j >= 0; j--) {
            c = mc[lm+mlen[j]];
            mc[lm+mlen[j]] = 0;
            ans[la++] = decode(&mc[lm]);
            mc[lm+mlen[j]] = c;
            lm += mlen[j];
        }
        ans[la] = 0;
        printf("%d: %s\n", i, ans);
    }
    return 0;
}
