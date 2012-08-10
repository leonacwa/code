#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#define N 4000
using namespace std;
bool ans[N];
bool judge(int n)
{
    int cnts = 0;
    		for (int i = 2; i <= n; ++i) {
			if (n % i == 0) {
				++cnts;
				while (n % i == 0) {
					n /= i;
				}
			}
		}
		if(cnts==2)return true;
		return false;
}
void init()
{
    memset(ans,0,sizeof(ans));
    for(int i= 2; i <N;i++){
        if(judge(i))ans[i]=true;
    }
}
int main()
{
    int n;
    init();
    while(~scanf("%d",&n)){
        //printf("%d--\n",prm[n]);
        int cnt = 0;
        for(int i = 1; i <=n;i++){
            if(ans[i])cnt++;
        }
        printf("%d\n",cnt);
    }

}
