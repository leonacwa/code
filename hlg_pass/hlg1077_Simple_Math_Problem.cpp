#include <stdio.h>

int main()
{
    int n;
    while (1 == scanf("%d", &n)){
        if (n <= 3){
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }
    return 0;
}
/*
long double fn(int n)
{
    long double sum = 0;
    int d = 1, i;
    for (i = 1; i <= n; i++){
        d *= i;
        sum += (long double)n / d;
    }
    return sum;
}
int main()
{
    int i;
    for (i = 1; i <= 100; i++){
        printf("%d:%lf\n", i, (double)fn(i));
    }
    return 0;
}/*
*/
