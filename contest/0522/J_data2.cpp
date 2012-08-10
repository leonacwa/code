#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
const int MAXN = 17320 +200;

bool is[MAXN] = {0};
int prm[MAXN];

int main()
{
    freopen("p.txt", "w", stdout);
	int cnt = 0;
	for (int i = 2; i <= MAXN; ++i) {
		if (false == is[i]) {
		    prm[cnt++] = i;
			for (int j = i + i; j <= MAXN; j += i) {
				is[j] = true;
			}
		}
	}
	printf("const int P_cnt = %d;\nconst int P[%d]={", cnt, cnt);
	for (int i = 0; i < cnt - 1; ++i) {
        printf("%d,", prm[i]);
	}
	printf("%d};", prm[cnt-1]);
	fclose(stdout);
	return 0;
}
