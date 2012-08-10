#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long llong;
llong n;
bool judge(llong a)
{
    if(a==1)return true;
    int t= 2;
    if(a&1)a--;
    while(a!=1){
        if(a%t!=0)break;
        while(a%t==0){
            a/=t;
            if(a==1)return true;
            t++;
        }
        //if(a==1)break;
        a--;
    }
    return false;
}
int main()
{
    while(~scanf("%lld",&n)){
        if(judge(n)){
            puts("YES");
        }
        else {
            puts("NO");
        }
    }
}
