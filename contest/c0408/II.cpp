
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define MAX 1000010
typedef long long  llong ;
bool Prime[MAX];
llong yz_num;
llong yz[100000]={0};
bool is[MAX]; llong prm[MAX];
llong pnum;
llong cnt;
llong getprm(llong n){
llong i, j, k = 1;
llong s, e = (llong)(sqrt(0.0 + n) + 1);
memset(is, 1, sizeof(is));
prm[k++] = 2; is[0] = is[1] = 0;
for (i = 4; i < n; i += 2) is[i] = 0;
for (i = 3; i < e; i += 2) if (is[i]) {
prm[k++] = i;
for (s = i * 2, j = i * i; j < n; j += s) is[j] = 0;
// 因为j是奇数，所以+奇数i后是偶数，不必处理！
}
for ( ; i < n; i += 2) if (is[i]) prm[k++] = i;
return k; // 返回素数的个数
}

llong kgcd(llong a, llong b){
if (a == 0) return b;
if (b == 0) return a;
if (!(a & 1) && !(b & 1)) return kgcd(a>>1, b>>1) << 1;
else if (!(b & 1)) return kgcd(a, b>>1);
else if (!(a & 1)) return kgcd(a>>1, b);
else return kgcd(abs(a - b), min(a, b));
}

void getyz(llong s)
{
llong ll,rr,w = 1;
yz_num=1;
yz[1]=1;
while (s!=1 && w <= pnum)
{
   rr=1;
   while (s%prm[w] == 0){
    ll=yz_num;
    for (llong i=rr;i<=ll;i++){
        yz_num++;
        yz[yz_num]=yz[i]*prm[w];
     }
    s/=prm[w];
    rr=ll+1;}
   w++;
}
if (s!=1){
   ll=yz_num;
   for (llong i=1;i<=ll;i++){
    yz_num++;
    yz[yz_num]=yz[i]*s;
    }
}
}


int main()
{
    pnum = getprm(MAX) ;
    llong m , n ;
    llong cases = 1 ;
    while( ~scanf("%lld %lld",&m,&n))
    {
        llong gcd = kgcd(m,n);
        m = m /gcd ;
        n = n /gcd ;
        memset(yz,0,sizeof(yz)) ;
        getyz(n * n);
        cnt = 0;
        for(llong i = 1 ; i <= yz_num ; i++)
        {
            if( (yz[i] + n ) % m == 0 && m * ( (yz[i] + n ) / m ) - n <= n )
            {
            cnt++ ;
            }
        }

        printf("Scenario #%lld\n", cases++);
        if(m > n || cnt == 0)
        puts("No solution");
        else if(cnt == 1)
        puts("Only one solution");
        else
        printf("Find %lld solutions\n", cnt);
        puts("");

    }
}
