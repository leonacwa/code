/* G  Panda */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define MAX  50010

using namespace std;
long long c[MAX];
long long sum;
char str[MAX];
int N,M,L,R;
long long ans;

int lowbit(int x)
{
    return x &(-x);
}

void update(int x,int val)
{
    while(x<=N) {
        c[x] += val;
        x += lowbit(x);
    }
}
long long get(int x)
{
    long long sum=0;
    while(x > 0) {
        sum += c[x];
        x -= lowbit(x);
    }
    return sum;
}

int main()
{
    int ca,cas = 1,op,po;
    char s[5];
    scanf("%d",&ca);
    while(ca--)
    {
        scanf("%d %d",&N,&M);
        memset(c,0,sizeof(c));
        //memset(sts,0,sizeof(sts));
        scanf("%s",str+1);
        for(int i=3;i<=N;i++)
        {
            if(str[i]=='w'&&str[i-1]=='b'&&str[i-2]=='w')
            update(i,1);
        }
        printf("Case %d:\n",cas++);
        for(int i=1;i<=M;i++)
        {
            scanf("%d",&op);
            if(op == 1)
            {
                scanf("%d %s",&po,s);
                po++;
                if(str[po]==s[0])continue;
                else
                {
                    if(po>=3&&str[po-1]=='b'&&str[po-2]=='w')
                    {
                        if(str[po]=='w')update(po,-1);
                        else update(po,1);
                    }
                    if(po>=2&&po<=N-1&&str[po-1]=='w'&&str[po+1]=='w')
                    {
                        if(str[po]=='b')update(po+1,-1);
                        else update(po+1,1);
                    }
                    if(po<=N-2&&str[po+1]=='b'&&str[po+2]=='w')
                    {
                        if(str[po]=='w')update(po+2,-1);
                        else update(po+2,1);
                    }
                    str[po]=s[0];
                }
            }
            else
            {
                scanf("%d %d",&L,&R);
                if(R-L<2) {printf("0\n"); continue;}
                ans = get(R+1)-get(L);
                if (1 <= L && L+2 <= N && str[L]=='w' && str[L+1]=='b' && str[L+2]=='w') ans--;
                if (1 <= L-1 && L+1 <= N && str[L-1]=='w' && str[L]=='b' && str[L+1]=='w') ans--;
                printf("%lld\n", ans);
            }
        }

    }

}
