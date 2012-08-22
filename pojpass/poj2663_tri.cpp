#include <cstdio>
#include <cstring>
using namespace std;

int n, f[3][5];
int main()
{
	while (EOF != scanf("%d", &n) && n > -1) {
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		f[1][1] = f[0][0];
		f[1][3] = f[0][0];
		for (int i = 2; i <= n; ++i) {
			int i0 = i % 3, i1 = (i - 1) % 3, i2 = (i - 2) % 3;
			f[i0][0] = f[i1][1] + f[i1][3] + f[i2][0];
			f[i0][1] = f[i1][0] + f[i1][4];
			f[i0][2] = f[i1][3];
			f[i0][3] = f[i1][0] + f[i1][2];
			f[i0][4] = f[i1][1];
		}
		printf("%d\n", f[n % 3][0]);
	}
	return 0;
}

