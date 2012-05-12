#include <iostream>
#include <cmath>
using namespace std;
bool prime(int k);

int main ()
{
	int x,y,i,j,k;
	bool flag,t;
	while (cin>>x>>y)
	{
		if (x == 0 && y ==0)
			break;
		for(i=x; i<=y; i++)
		{
			j = i*i+i+41;
			flag = prime(j);
			if(!flag) {
				break;
			}
		}
		if(flag) 
			cout<<"OK"<<endl;
		else 
			cout<<"Sorry"<<endl; 
	}
	return 0;
} 

bool prime(int k)
{
	int i, n = (int)sqrt(k);
	for(i=2;i<=n;i++)
		if(k%i == 0) {
			return false;
		}
	return true;
}
