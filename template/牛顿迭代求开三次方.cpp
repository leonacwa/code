#include <iostream>
using namespace std;

double abs(double a)
{
    if(a<0)return -a;
    return a;
}

double sqrt3(double a)
{
    double root =1.0;
    while( abs(root*root*root - a)>=1e-8)
        root = root - (root*root*root-a)/(3*root*root);
    return root;
}

int main()
{
     double root;
     cout<<(root=sqrt3(8.0))<<endl;
     cout<<root*root*root<<endl;
     system("pause");
     return 0;
}
