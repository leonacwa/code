// http://acm.hrbeu.edu.cn/index.php?act=problem&id=1005&cid=18
//  
//总结： 广搜，他妈的我全忘记了，导致频频出错, 函数参数的意义没有真正注意到，导致出差错 
 
#include <iostream>
using namespace std;

char map[10][11];

struct Node{int x, y; char c;} arr[100];
struct {int x, y;} que[128];

int _cnt;
char ans[50];
int _tot;

bool cmp(const struct Node &a, const struct Node &b)
{
     return a.c < b.c;
}

int bfs(int x, int y, char c);
int find(int x, int y)
{
    for (int i = 0; i < _cnt; i++)
    if(x == arr[i].x && y == arr[i].y)
        return i;
    return -1;
}
bool Nosign(int x, int y, int tot)
{
     for (int i = 0; i <= tot; i++)
     {
         if (que[i].x == x && que[i].y == y)
             return false;
     }
     return true;
}
int main()
{
    int n, i, j, cnt, pre_cnt;
    
    scanf("%d", &n);
    while (n--)
    {
        _cnt = 0;
        for (i = 0; i < 10; i++)
        {
            scanf("%s", map[i]);
            for (j = 0; j < 10; j++)
            if (map[i][j] >= 'A' && map[i][j] <= 'Z')
            {
                arr[_cnt].x = i;
                arr[_cnt].y = j;
                arr[_cnt].c = map[i][j];
                _cnt++;
            }
        }
        sort(arr, arr + _cnt, cmp);
        _tot = 0;
        cnt = _cnt;
        
        pre_cnt = -2;
    
        while (pre_cnt != cnt && cnt > 0) // again
        {
            pre_cnt = cnt;
            for (i = 0; i < _cnt; i++)
            {
                //
                if (map[arr[i].x][arr[i].y] != '.')
                {
                    if ( -1 != bfs(arr[i].x, arr[i].y, map[arr[i].x][arr[i].y]))
                    {
                        cnt -= 2;
                        break;
                    }
                }
            }
        }
        
        if (cnt == 0)
        {
            ans[_tot] = 0;
            printf("%s\n", ans);
        }
        else
        {
            printf("My God!\n");
        }
        
    }
    return 0;
}

int bfs(int x, int y, char c)
{
     int tot, cur;
     
     tot = cur = 0;
     que[tot].x = x;
     que[tot].y = y;
     
     do
     {
         x = que[cur].x;
         y = que[cur].y;
         cur++;
         if (x > 0 && (map[x-1][y] == '.' || map[x-1][y] == c) && Nosign(x-1, y, tot))
         {
             ++tot;
             que[tot].x = x - 1;
             que[tot].y = y;
             if (map[x-1][y] == c)
             {
                 cur = tot;
                 break; 
             }
         }
         if (x < 9 && (map[x+1][y] == '.' || map[x+1][y] == c) && Nosign(x+1, y, tot))
         {
             ++tot;
             que[tot].x = x + 1;
             que[tot].y = y;
             if (map[x+1][y] == c)
             {
                 cur = tot;
                 break; 
             }
         }
         if (y > 0 && (map[x][y-1] == '.' || map[x][y-1] == c) && Nosign(x, y-1, tot))
         {
             ++tot;
             que[tot].x = x;
             que[tot].y = y - 1;
             if (map[x][y-1] == c)
             {
                 cur = tot;
                 break; 
             }
         }
         if (y < 9 && (map[x][y+1] == '.' || map[x][y+1] == c)&& Nosign(x, y+1, tot))
         {
             ++tot;
             que[tot].x = x;
             que[tot].y = y + 1;
             if (map[x][y+1] == c)
             {
                 cur = tot;
                 break; 
             }
         }
     }while (cur <= tot);

     if (cur <= tot && map[que[cur].x][que[cur].y] == c)
     {
         map[que[cur].x][que[cur].y] = '.';
         map[que[0].x][que[0].y] = '.';
         ans[_tot++] = c;
         return find(que[cur].x, que[cur].y);
     }
     return -1;
}
