/**
  计数问题
   http://acm.hrbeu.edu.cn/index.php?act=problem&id=1001&cid=17
   题意：十进制a和b之间1出现的次数。
   
**/

#include <stdio.h>

const int ten[10]={0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int count(int x) /**精髓所在*/
{
    if (x < 0)
        return 0;
    
    int k, xx = x, sum = 0, i;
    
    k = x % 10;
    x /= 10;
    
    /*
    if (k >= 2){
        sum = x + 1;
    }
    else if (k == 1){
        sum = x + 1;
    }
    else if (k == 0){
        sum = x;
    }
    */
    if (k > 0){
        sum = x + 1;
    }
    else{ /*k == 0 */
        sum = x;
    }
    for (i = 1; x; i++){
        k = x % 10;
        x /= 10;
        if (k >= 2){
            sum += (x+1) * ten[i];
        }
        else if (k == 1){
            sum += x * ten[i] + (1 + xx % ten[i]);
        }
        else /*if (k == 0){*/
            sum += x * ten[i];
        /*}*/
    }
    return sum;
}

int main()
{
    int a, b;
    while (2 == scanf("%d %d", &a, &b) && (a|b)){
        if (a > b){
            a = a ^ b;
            b = a ^ b;
            a = a ^ b;
        }
        printf("%d\n", count(b) - count(a-1));
    }
    return 0;
}
