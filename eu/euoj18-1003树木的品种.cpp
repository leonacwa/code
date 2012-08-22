//http://acm.hrbeu.edu.cn/index.php?act=problem&id=1003&cid=18

#include <iostream>
using namespace std;


char str[1000000][32];

struct {char name[32]; int count;} tree[10000]; 

int cmp(const void *a, const void * b)
{
    return strcmp((const char*)a, (const char*)b);
}
int main()
{
    int i, cnt, total;
    
    total = 0;
    while(NULL != gets(str[total]))
       total++;
    
    qsort(str, total, sizeof(char)*32, cmp);
    
    cnt = 1;
    for (i = 0; i < total; i++)
    {
        if(0 == strcmp(str[i], str[i+1]))
            cnt++;
        else
        {
             printf("%s %0.4f\n", str[i], 100.0*(double)cnt / total);
             cnt = 1;
        }
    }
  
    system("pause");
    return 0;
}
