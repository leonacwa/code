/// Brackets! Brackets!
#include <stdio.h>
#include <string.h>
int main()
{
    int tt;
    char br[256], *pb;
    char s[256];
    int s_top;
    scanf("%d", &tt);
    gets(br);
    while (tt-- && gets(br)){
        s_top = -1;
        for (pb = br; *pb; pb++){
            if (*pb == '(' || *pb == '[' || *pb == '{')
                s[++s_top] = *pb;
            else {
                if (s_top >= 0
                    && ((s[s_top] == '(' && *pb == ')')
                      ||(s[s_top] == '[' && *pb == ']')
                      ||(s[s_top] == '{' && *pb == '}')) )
                    s_top--;
                else
                    break;
            }
        }
        if (*pb == '\0' && s_top == -1)
            printf("Valid\n");
        else
            printf("Invalid\n");
    }
    return 0;
}
