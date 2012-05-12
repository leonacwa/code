//http://acm.hrbeu.edu.cn/index.php?act=problem&id=1004&cid=18
#include <iostream>
using namespace std;

char map[51][51];
int n, m, ans;

void dfs(int, int);

int main()
{
    int i, j;
    
    while(EOF != scanf("%d %d", &n, &m))
    {
        memset(map, 0, sizeof(char)*51*51);
        for (i = 0; i < n; i++)
            scanf("%s", map[i]);
        
        ans = 0;
        for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            if (map[i][j] == '@')
            {
                dfs(i, j);
                ans++;
            }
            
        }
        printf("%d\n", ans);
    }
    return 0;
}

void dfs(int i, int j)
{
    map[i][j] = 1;
    if (i > 0 && map[i-1][j] == '@' )
        dfs(i-1, j);
    if (i+1 < n && map[i+1][j] == '@')
        dfs(i+1, j);
    if (j > 0 && map[i][j-1] == '@')
        dfs(i, j-1);
    if (j+1 < m && map[i][j+1] == '@')
        dfs(i, j+1);
}
