//http://acm.hrbeu.edu.cn/index.php?act=problem&id=1002&cid=18

#include <iostream>
using namespace std;

char dna[20000+1][24];

int cmp(const void *a, const void * b)
{
    return strcmp((const char*)a, (const char*)b);
}
int main()
{
    int m, n, i, cnt;
    int count[20000 + 1];
    
    scanf("%d %d", &n, &m);
    while (n != 0 && m != 0)
    {
        for (i = 0; i < n; i++)
            scanf("%s", dna[i]);
        qsort(dna, n, sizeof(char)*24, cmp);
        
        memset(count, 0, sizeof(int)*(20000 + 1));
        
        cnt = 0;
        for (i = 1; i < n; i++)
        {
            if(0 == strcmp(dna[i], dna[i-1]))
                cnt++;
            else
            {
                count[cnt]++;
                cnt = 0;
            }
        }
        count[cnt]++;
        for (i = 0; i < n; i++)
        {
            printf("%d\n", count[i]);
        }
        scanf("%d %d", &n, &m);
    }   
    return 0;
}
