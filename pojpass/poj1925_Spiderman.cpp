/* Spiderman swing 一次遵循能量守恒，每次swing的起始纵坐标和终止的纵坐标是一样的，这点很关键！
 * */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
using namespace std;

const int MAXN = 5000+5;
const int MAXX = 1000000+5;

int x[MAXN], y[MAXN];
int f[MAXX];
int N;

int main()
{
	int caseN;
	scanf("%d", &caseN);
	while (caseN--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &x[i], &y[i]);
		}
		memset(f, -1, sizeof(f));
		f[x[0]] = 0;
		for (int i = 1; i < N; i++) { // 坐标范围0..10^6，需要double，int存不下
			for (int j = max(x[0], x[i] - (int)sqrt(((double)y[i])*y[i] - ((double)y[i]-y[0])*(y[i]-y[0]))); j < x[i]; j++) {
				int a = x[i] + x[i] - j;
				if (a > x[N-1]) {
					a = x[N-1];
				}
				if (f[j] != -1 && (f[a] == -1 || f[a] > f[j] + 1)) {
					f[a] = f[j] + 1;
				}
			}
		}
		printf("%d\n", f[x[N-1]]);
	}
	return 0;
}

