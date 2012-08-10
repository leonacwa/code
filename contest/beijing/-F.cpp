/*  F  Machine scheduling */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;
const int maxn = 1010;
int c[maxn][maxn]; int s[maxn][maxn]; int f[maxn][maxn];
int g[maxn][maxn];
const int mm=1000000007;
int n,r,m,k;
int getG(int m,int r) {
    if (m==0&&r==0) return 1;
    if (r<=0) return 0;
    if (m<r) return 0;
    return g[m][r];
}
void init()
{
    int i,j,k; int  temp;
    memset(c,sizeof(c),0); memset(s,sizeof(s),0); memset(f,sizeof(f),0);
    for (i=1;i<maxn;i++) c[i][0]=1;
    for (k=1;k<maxn;k++) for (i=k;i<maxn;i++)
    {
        if (i==k) c[i][k]=1;
        else c[i][k]=(c[i-1][k]+c[i-1][k-1])%mm;
    }
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    for (i=0;i<maxn;i++) {
        for (j=0;j<maxn;j++) {
            g[i][j]=(getG(i-1,j-1)+(long long)j*getG(i-1,j))%mm;
            //printf("g[%d][%d]=%d\n",i,j,g[i][j]);
            if (j>0) {
                f[i][j]=(f[i][j-1]+g[i][j])%mm;
            }
        }
    }

}
int main()
{

    long long res=0;
    init();
    //cout<<"over"<<endl;
    //int a,b; while (cin>>a>>b) cout<<s[a][b]<<endl;
    //int a,b; while (cin>>a>>b) cout<<f[a][b]<<endl;
    while (cin>>n>>r>>k>>m)
    {
        int t = n-(r-1)*(k-1);
        if (k==0) t = n;
        if (t<r) {
            res=0;
            cout<<res<<endl;
            continue;
        }
        if (m-1>r-1) m=r;
        //cout<<c[t][r]<<endl;
        //cout<<f[r][m]<<endl;
        cout<<((long long)c[t][r]*f[r][m]%mm)<<endl;
    }
}
