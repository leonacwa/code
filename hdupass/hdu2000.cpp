#include <iostream>
using namespace std;
int main()
{
        char a, b, c, d;
        while (cin >> a >> b >> c) {
                if(a > c) {
                        d = c;
                        c = a;
                        a = d;
                }
                if(a > b) {
                        d = b;
                        b = a;
                        a = d;
                }
                if(b > c) {
                        d = c;
                        c = b;
                        b = d;
                }
                cout << a << " " << b << " " << c << endl;
        } 
        return 0;
}
