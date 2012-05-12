/// 
#include <stdio.h>
#include <string.h> 

char map[5][10];
int sum_k[9][9];

int max(int a, int b){return a>b?a:b;}
int min(int a, int b){return a<b?a:b;}

void init_sum_k(int t)
{
    int l, r;
    memset(sum_k, 0, sizeof(sum_k));
    for (l = 0; l < 9; l++){
        if (map[t][l] == 'K')
            sum_k[l][l] = 1;
        for (r = l+1; r < 9; r++){
            sum_k[l][r] = sum_k[l][r-1];
            if (map[t][r] == 'K')
                sum_k[l][r]++;
        }
    }
}
int go(int l, int t, int k)
{
    if (l < 0 || l > 8 || t < 0 || t > 4 || k < 0)
        return 0;
    if (map[t][l] == 0)
        return 0;
    
    int res = 0, _max = 0;
    char c = map[t][l];
    map[t][l] = 0;
    
    if (c == 'K')
        res = 1;
    
    if (k == 0){
        map[t][l] = c;
        return res;
    }
    
    _max = 0;
    
    if (t > 0)
        _max = go(l, t-1, k-1);
    
    if ( 0 < l )
        _max = max(_max, go(l-1, t, k-1));
    
    if ( l < 8 )
        _max = max(_max, go(l+1, t, k-1));
    
    map[t][l] = c;
    return res + _max;
}

int main()
{
    int i, j, l, t, tt, total_k, ans, k;

    scanf("%d", &tt);
    while(tt--){
        if (1 != scanf("%d", &k))
            break;
        gets(map[0]);
        total_k = 0;
        t = -1;
        for (i = 0; i < 5; i++){
            gets(map[i]);
            if (t == -1)
            for (l = 0; l < 9; l++){
                if ('L' == map[i][l]){
                    t = i;
                    break;
                }
            }
        }
        total_k = 0;
        for (i = 0; i <= t; i++)
            for (j = 0; j < 9; j++)
                if ('K' == map[i][j])
                    total_k++;
        
        int ll, rr, tmp;
        
        if (k >= (1+t)*9+min(l, 8-l))
            ans = total_k;
        else{
            /// 简化问题，上部的0~t-1当做不可重复走的过河卒问题，t行枚举走路的步数
            init_sum_k(t);
            ans = 0;
            for (ll = 0; ll < 9; ll++){
                for (rr = 0; rr < 9; rr++) if (k-1-ll-rr >= -1) {
                    if (0 <= l - ll && l+(rr-ll) <= 8){ /// left first
                        tmp = sum_k[l-ll][max(l, l-ll+rr)] 
                             + go(l-ll+rr, t-1, k-1-ll-rr);
                        ans = max(ans, tmp);
                    }
                    
                    if (l+rr<=8 && l+rr-ll>=0){ /// right first
                        tmp = sum_k[min(l, l+rr-ll)][l+rr] 
                             + go(l+rr-ll, t-1, k-1-ll-rr);
                        ans = max(ans, tmp);
                    }
                }
            }
            
        }
        
        printf("%d\n", ans);
        
    }
    return 0;
}
