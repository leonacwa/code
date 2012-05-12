#include <stdio.h>
const int ten[10]={0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
int count(int x) /**¾«ËèËùÔÚ*/
{
    if (x < 0)
        return 0;    
    int k, xx = x, sum = 0, i;    
    k = x % 10;
    x /= 10;    
    if (k > 0)
        sum = x + 1;
    else
        sum = x;
    for (i = 1; x; i++){
        k = x % 10;
        x /= 10;
        if (k > 1)
            sum += (x+1) * ten[i];
        else if (k == 1)
            sum += x * ten[i] + 1 + xx % ten[i];
        else
            sum += x * ten[i];
    }
    return sum;
}

int main()
{
    int a, b;
    while (scanf("%d %d", &a, &b) && (a|b)){
        if (a > b){
            a = a ^ b;
            b = a ^ b;
            a = a ^ b;
        }
        printf("%d\n", count(b) - count(a-1));
    }
    return 0;
}
