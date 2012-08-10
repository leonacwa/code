#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define N 35
using namespace std;
int n;
char str[N];
char result[N];
int main()
{
    int ca = 1;
    while(~scanf("%d",&n)){
        memset(result,'\0',sizeof(result));
        for(int i = 0; i < 2 * n - 1; i++){
            scanf("%s",str);
            for(int i = 0; i <strlen(str);i++){
                result[i] ^= str[i];
            }
        }
        printf("Scenario #%d\n",ca++);
        printf("%s\n\n",result);

    }
}
