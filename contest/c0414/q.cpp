#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
bool rmq[1000001];
int count1[1000001];
int prim[1000000];
int sum1;
void makermq(){
	memset(rmq,true,sizeof(rmq));
	rmq[0]=rmq[1]=false;
	for (int i = 2; i <= 20000; ++i) {
		if (rmq[i]) {
			for (int j = i+i; j <= 1000000; j += i) {
				rmq[j] = false;
			}
		}
	}
	sum1 = 0;
	for(int i=2;i<=1000000;i++)
		if(rmq[i])
			prim[sum1++]=i;
}

int main(){
	long long n,m;
	int k,iCase;
	makermq();
	cin>>iCase;
	while(iCase--){
		cin>>n;
		int sum=1;
		m = n;
		int cnt = 0;
		for (int i = 0; i < sum1; ++i) {
			if (m % prim[i] == 0) {
				count1[cnt] = 0;
				while(m % prim[i] == 0){
					count1[cnt]++;
					m /= prim[i];
				}
				++cnt;
			}
			if(m == 1)
				break;
		}
		for(int j=0;j < cnt;j++){
			sum=sum*(2*count1[j]+1);
		}
		if(m!=1)
			sum*=3;
		cout<<sum<<endl;
	}
	return 0;
}

