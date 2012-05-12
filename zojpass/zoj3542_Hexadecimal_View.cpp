/* zoj 3542 Hexadecimal View */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[4096+128];

int main()
{
    int i, a, st, sl;
    while (gets(s) && s) {
        sl = strlen(s);
        for (a = 0; a < sl; ++a) {
            if (a % 16 == 0) {
                if (a) printf("\n");
                printf("%04x: ", a);
                st = a;
            }
            printf("%x", s[a]);
            if (a%2 == 1) printf(" ");
            if ((a+1) % 16 == 0 || s[a+1] == '\0') {
                if ((a+1) % 16) {
                    for (i = a+1; i < st+16; i++) {
                        printf("  ");
                        if (i%2 == 1) printf(" ");
                    }
                }
                for (i = st; i <= a; i++) {
                    if (isalpha(s[i])) {
                        if (isupper(s[i])) putchar(tolower(s[i]));
                        else putchar(toupper(s[i]));
                    } else printf("%c", s[i]);
                }
            }
        }
        puts("");
    }
    return 0;
}
