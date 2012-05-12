/** poj 1023 The Fun Number System */
#include <iostream>
using namespace std;
typedef long long llong;

int main()
{
    llong N;
    char b[65], ks[65];
    int tt, k, i;
    cin >> tt;
    while (tt--) {
        cin >> k >> ks >> N;
        b[k] = 0;
        for (i = k-1; i >= 0; i--) {
            if (N & 1) {
                b[i] = '1';
                if (ks[i] == 'n'){
                    N += 2;
                }
            }
            else {
                b[i] = '0';
            }
            N >>= 1;
        }
        if (N) {
            cout << "Impossible\n";
        }
        else {
            cout << b << endl;
        }
    }
    return 0;
}
