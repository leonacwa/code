// NOIP 2009  sudoku 靶形数独
/*
  DFS, 得把分数表打印出来，然后就没什么好说的了.
  但是悲剧的WA了一半的测试点，这个DFS太单纯啊。
*/
#include <stdio.h>
#include <string.h>

const int score[9][9] ={
{6, 6, 6, 6, 6, 6, 6, 6, 6},
{6, 7, 7, 7, 7, 7, 7, 7, 6},
{6, 7, 8, 8, 8, 8, 8, 7, 6},
{6, 7, 8, 9, 9, 9, 8, 7, 6},
{6, 7, 8, 9, 10,9, 8, 7, 6},
{6, 7, 8, 9, 9, 9, 8, 7, 6},
{6, 7, 8, 8, 8, 8, 8, 7, 6},
{6, 7, 7, 7, 7, 7, 7, 7, 6},
{6, 6, 6, 6, 6, 6, 6, 6, 6}
};

struct Pos{
    int x, y;
};
Pos p[9*9+1], pt;
int pi;

int sd[9][32];
bool sq[3][3][10], r[9][10], c[9][10];
int sum, max;

void dfs(int s, int sum)
{
    if (s >= pi){
        if (max < sum)
            max = sum;
        return;
    }
    
    for (int i = 9; i >= 1; i--)
    if (!sq[p[s].x/3][p[s].y/3][i] && !r[p[s].x][i] && !c[p[s].y][i]){
        
        sd[p[s].x][p[s].y] = i;
        sq[p[s].x/3][p[s].y/3][i] = true;
        r[p[s].x][i] = true;
        c[p[s].y][i] = true;
        
        dfs(s+1, sum+score[p[s].x][p[s].y]*i);
        
        sd[p[s].x][p[s].y] = 0;
        sq[p[s].x/3][p[s].y/3][i] = false;
        r[p[s].x][i] = false;
        c[p[s].y][i] = false;
    }
}
int main()
{
    freopen("sudoku.in", "r", stdin);
    freopen("sudoku.out", "w", stdout);
    
    memset(sq, 0, sizeof(sq));
    memset(r, 0, sizeof(r));
    memset(c, 0, sizeof(c));
    
    pi = 0; sum = 0;
    
    for (int i = 0; i < 9; i++){
        
        for (int j = 0; j < 9; j++){
            scanf("%d", &sd[i][j]);
            //sd[i][j] -= '0';
            
            sq[i/3][j/3][sd[i][j]] = true;
            r[i][sd[i][j]] = true;
            c[j][sd[i][j]] = true;
            
            sum += sd[i][j]*score[i][j];
            
            if (sd[i][j] == 0){
                p[pi].x = i;
                p[pi].y = j;
                pi++;
            }
        }
    }
    
    for (int i = 0, k; i < pi-1; i++){
        k = i;
        for (int j = i+1; j < pi; j++){
            if (score[p[k].x][p[k].y] > score[p[j].x][p[j].y]) // 人品吗？改为分数低的在前，就过了好多点
                k = j;
        }
        pt = p[i];
        p[i] = p[k];
        p[k] = pt;
    }

    max = -1;
    for (int i = 9; i >= 1; i--){
    if (!sq[p[0].x/3][p[0].y/3][i] && !r[p[0].x][i] && !c[p[0].y][i]){
        
        sd[p[0].x][p[0].y] = i;
        sq[p[0].x/3][p[0].y/3][i] = true;
        r[p[0].x][i] = true;
        c[p[0].y][i] = true;
        
        dfs(1, sum+score[p[0].x][p[0].y]*i);
        
        sd[p[0].x][p[0].y] = 0;
        sq[p[0].x/3][p[0].y/3][i] = false;
        r[p[0].x][i] = false;
        c[p[0].y][i] = false;
    }
    }
    
    printf("%d\n", max);
    
    fclose(stdin);
    fclose(stdout);
    
    return 0;
}
