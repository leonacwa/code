#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 3 * 100000000;
const int LEN = 50000;

bool is[MAXN] = {0};

int main()
{
    freopen("l.txt", "w", stdout);
	int cnt = 0;
	printf("const int C[%d]={", MAXN / LEN);
	for (int i = 2; i < MAXN; ++i) {
		if (false == is[i]) {
			if (0 == ((i - 1) % 4) || i == 2) {
				++cnt;
			}
			for (int j = i + i; j <= MAXN; j += i) {
				is[j] = true;
			}
		}
		if (i % LEN == 0) {
				printf("%d,", cnt);
        }
	}
	printf("%d};", cnt);
	fclose(stdout);
	return 0;
}
