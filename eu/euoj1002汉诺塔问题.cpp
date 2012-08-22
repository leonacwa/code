//http://acm.hrbeu.edu.cn/index.php?act=problem&id=1002&cid=17
//ººÅµËþ
#include <iostream>
using namespace std;

void move(int n, char a, char c)
{
     printf("move %d from %c to %c\n", n, a, c);
}
void hanoi(int n, char a, char b, char c)
{
    if (n == 1)
        move(n, a, c);
    else
    {
        hanoi(n-1, a, c, b);
        move(n, a, c);
        hanoi(n-1, b, a, c);
    }
}

int main()
{
    int n;
    
    cin >> n;
    hanoi(n, 'a', 'b', 'c'); 
    return 0;
}
