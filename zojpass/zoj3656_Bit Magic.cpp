/* ZOJ 3656 Bit Mabic
 * 囧~都说是2-SAT做的，但是可以不用
 * 因为按照题目要求，如果a[0]的值确定了，根据b[][]，a[]就全部确定了，直接枚举a[0]=0,1就行了，然后判断是否合法
 * */
#include <cstdio>
#include <cstring>

const int MAXN = 501;
int n;
int _b[MAXN][MAXN];
bool b[MAXN][MAXN];
bool a[MAXN];

bool try_it(bool v) {
	// a[0]确定了,i为奇数时，根据b[0][i]，a[i]就确定了，得到a[1]，当i为偶数时，根据b[1][i]，a[i]就确定了，那么a数组就都确定了
	a[0] = v;
	for (int i = 1; i < n; i += 2) a[i] = a[0] ^ b[0][i];
	for (int i = 2; i < n; i += 2) a[i] = a[1] ^ b[1][i];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				if (b[i][j] != 0) return false;
			} else if (i % 2 == 1 && j % 2 == 1){
			   	if (b[i][j] != (a[i] | a[j])) return false;
			} else if (i % 2 == 0 && j % 2 == 0) {
				if (b[i][j] != (a[i] & a[j])) return false;
			} else if (b[i][j] != (a[i] ^ a[j])) return false;
		}
	}
	return true;
}

int main() {
	while (EOF != scanf("%d", &n)) {
		bool ok = true;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%d", &_b[i][j]);
			}
		}
		for (int bit = 0; bit < 32; ++bit) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j <  n; ++j) {
					b[i][j] = _b[i][j]>>bit & 1;
				}
			}
			if (!try_it(0) && !try_it(1)) {
				ok = false;
				break;
			}
		}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}
