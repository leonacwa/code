// http://acm.hrbeu.edu.cn/index.php?act=problem&id=1385
// hrbeu 1358  01串
/* 关键代码：这个方程还是很容易想出来的，我当时是把阶段给弄错了
       for (i = 4; i <= n; i++){ // 把阶段写错了，其实是从第四个字符开始的，我废啊
            memset(f[i%2], 0, sizeof(int)*8); //printf("memset\n");
            for (j = 0; j < 8; j++){
                if (!_01[j])
                    continue;
                k = (j << 1) & 6;
                if (_01[k])
                    f[i%2][k] = (f[i%2][k] + f[(i-1)%2][j]) % mydiv;
                k |= 1;
                if (_01[k])
                    f[i%2][k] = (f[i%2][k] + f[(i-1)%2][j]) % mydiv;
            }
        }
  

*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int mydiv = 99999;

int f[2][8];
int sum;
bool _01[8];

int str2int(char* s)
{
    int i;
    i  = ((s[0] == '1') << 2);
    i += ((s[1] == '1') << 1);
    i +=  (s[2] == '1');
    return i;
}
/*
void printi(int i)
{
    printf("%d%d%d\n", (i >> 2)&1, (i >> 1)&1, i & 1);
}
*/
int main()
{
    int i, j, n, m, t, k;
    char str[8];
    
    while (EOF != scanf("%d %d", &n, &m)){        
        memset(_01, 0, sizeof(bool)*8);        
        for (i = 0; i < m; i++){
            scanf("%s", str);
            t = str2int(str); //printf("%d:", t); printi(t);
            _01[t] = true;  
        }
        
        if (n < 3){
            printf("%d\n", n==0?0:(1<<n));  //printf("%d < 3\n", n);
            continue;
        }
        
        memset(f[1], 0, sizeof(int)*8); 
        for (j = 0; j < 8; j++){
            if (_01[j]){
                f[1][j]++;
            }
        }
        
        for (i = 4; i <= n; i++){ // 把阶段写错了，其实是从第四个字符开始的，我废啊
            memset(f[i%2], 0, sizeof(int)*8); //printf("memset\n");
            for (j = 0; j < 8; j++){
                if (!_01[j])
                    continue;
                k = (j << 1) & 6; // printi(k);
                if (_01[k])
                    f[i%2][k] = (f[i%2][k] + f[(i-1)%2][j]) % mydiv;
                k |= 1;
                if (_01[k])
                    f[i%2][k] = (f[i%2][k] + f[(i-1)%2][j]) % mydiv;
            }
        }

        sum = 0;
        for (j = 0; j < 8; j++){
            if (_01[j])
                sum = (sum + f[n%2][j]) % mydiv;
        }
        printf("%d\n", sum % mydiv);
    }
    return 0;
}
