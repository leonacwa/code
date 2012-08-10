 1001 ( A Card Game )     Judge Status : Accepted
RunId : 1222    Language : G++    Author : 
Code Render Status : Rendered By HDOJ G++ Code Rander Version 0.01 Beta
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=1000+200;
int a[maxn];
int m,t,icase;
double sum;
int main()
{
    icase=1;
    cin>>t;
    while(t--)
    {
        cin>>m;    
        sum=0;
        for(int i=1;i<=m;i++)
        {
            cin>>a[i];
            sum+=a[i]; 
        }
        printf("Case %d: %.6lf\n",icase++,a[1]/sum);
    }
    return 0;
}

