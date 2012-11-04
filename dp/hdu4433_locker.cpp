/*
 * HDU 4433 locker
 * Asia 2012 ACM-ICPC Tianjin C. locker
 111111 222222
 896521 183995

 2
 12
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
const unsigned char INF_BYTE = 0x3f;

int f[MAXN][10][10];
char sa[MAXN], sb[MAXN];

template <class T>
void check_min(T &a, const T &b) {
	if (b < a) a = b;
}

int main() {
	while (EOF != scanf("%s%s", sa+1, sb+1)) {
		int ls = strlen(sa+1);
		for (int i = 1; i <= ls; ++i) {
			sa[i] -= '0';
			sb[i] -= '0';
		}
		if (ls == 1) {
			printf("%d\n", min((sa[1] - sb[1] + 10)%10, (sb[1] - sa[1] + 10)%10) );
			continue;
		}
		memset(f, INF_BYTE, sizeof(f));
		f[2][sa[1]][sa[2]] = 0;
		for (int i = 2; i <= ls + 2; ++i) {
			for (int a = 0; a < 10; ++a) {
				for (int b = 0; b < 10; ++b) {
					if (f[i][a][b] == INF) continue;
					int t = (sb[i-1] - a + 10) % 10;
					for (int h = 0; h <= t; ++h) {
						for (int k = 0; k <= h; ++k) {
							check_min(f[i+1][(b+h)%10][(sa[i+1]+k)%10], f[i][a][b] + t);
						}
					}
					t = 10 - t;
					for (int h = 0; h <= t; ++h) {
						for (int k = 0; k <= h; ++k) {
							check_min(f[i+1][(b-h+10)%10][(sa[i+1]-k+10)%10], f[i][a][b] + t);
						}
					}
				}
			}
		}
		int ans = INF;
		for (int a = 0; a < 10; ++a) {
			for (int b = 0; b < 10; ++b) {
				if (ans > f[ls+2][a][b]) ans = f[ls+2][a][b];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
