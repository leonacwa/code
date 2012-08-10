/* 1006 ( Random Sequence )     Judge Status : Accepted
RunId : 5040    Language : C++    Author : 
Code Render Status : Rendered By HDOJ C++ Code Rander Version 0.01 Beta
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int M = 1502;
double arr[M];
int n;
int main()
{
    int ncase ;
    arr[1] = 1; arr[2] = 1.5;
    double mid = 0.5;

    for(int i = 3; i < 1502;i++)
    {
        arr[i] = arr[i-1] + mid;
        if(i % 2 == 1) mid = mid*((i)*1.0/(i+1));
    }

    scanf("%d", &ncase);
    for(int j = 0; j < ncase; j++)
    {
        scanf("%d", &n);
        printf("Case %d: ", j+1);
        printf("%.6lf\n",arr[n]);
    }
    return 0;
}