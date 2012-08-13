/* Ticket to Ride
 * 动态规划 + Minimal Steiner Tree
 * */
#include <cstdio>
#include <string>
#include <map>
using namespace std;

const int MAXN = 30, INF = 99999999;
int mat[MAXN][MAXN];
int f[1<<8][MAXN];
int id[8];
char v[MAXN];

int main() {
	int n, m;
	while (EOF != scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		map<string, int> ma;
		char str1[256], str2[256];
		for (int i = 0; i < n; ++i) {
			scanf("%s", str1);
			ma[str1] = i;
		}
		for (int i = 0; i < n; ++i)  {
			mat[i][i] = 0;
			for (int j = i+1; j < n; ++j) mat[i][j] = mat[j][i] = INF;
		}
		for (int i = 0, a, b, c; i < m; ++i) {
			scanf("%s%s%d", str1, str2, &c);
			a = ma[str1], b = ma[str2];
			if (mat[a][b] > c) {
				mat[a][b] = mat[b][a] = c;
			}
		}
		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = i+1; j < n; ++j) {
					if (mat[i][j] > mat[i][k] + mat[k][j]) 
						mat[i][j] = mat[j][i] = mat[i][k] + mat[k][j];
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			scanf("%s", str1);
			id[i] = ma[str1];
			for (int j = 0; j < n; ++j) {
				f[1<<i][j] = mat[j][id[i]];
			}
		}
		for (int i = 1; i < 256; ++i) {
			if (!(i & (i-1))) continue;
			for (int j = 0; j < n; ++j) {
				v[j] = 0;
				f[i][j] = INF;
				for (int k = 1; k < i; ++k) {
					if ((i|k) == i) {
						if (f[i][j] > f[k][j] + f[i-k][j]) 
							f[i][j] = f[k][j] + f[i-k][j];
					}
				}
			}
			for (int j = 0, b, c, k; j < n; ++j) {
				b = INF;
				for (k = 0; k < n; ++k) {
					if (b > f[i][k] && !v[k])
						b = f[i][c=k];
				}
				for (k = 0, v[c] = 1; k < n; ++k) {
					if (f[i][c] > f[i][k] + mat[k][c]) 
						f[i][c] = f[i][k] + mat[k][c];
				}
			}
		}
	   	// 利用了掩码的方法，枚举每组点的掩码，相同掩码分在一组
		int ans = INF;
		for (int i = 0; i < 256; ++i) {
			int z = 0;
			for (int j = 0; j < 4; ++j) {
				int y = 0, x;
				for (int k = 0; k < 8; k += 2) {
					if (((i>>k)&3) == j) 
						y += 3<<k, x = id[k];
				}
				if (y) z += f[y][x];
			}
			if (ans > z) ans = z;
		}
		printf("%d\n", ans);
	}
	return 0;
}
