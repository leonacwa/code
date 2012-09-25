#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

typedef long long int64;
typedef map<int64, int> MII;
char s[32];

int main() {
	while (EOF != scanf("%s", s)) {
		if (s[0] == 'E') break;
		MII bf[15], af[15];
		int ls = strlen(s);
		for (int i = 0; i < ls - 1; ++i) {
			int64 d = s[0] - '0';
			if (i == 0) {
				bf[i][d]++;
				continue;
			}
			int64 sum = 0;
			for (int j = (1<<i) - 1; j >= 0; --j) {
				d = s[0] - '0';
				sum = 0;
				for (int k = 0; k < i; ++k) {
					if (j & (1<<k)) {
						d = d * 10 + s[k+1] - '0';
					} else {
						sum += d;
						d = s[k+1] - '0';
					}
				}
				sum += d;
				bf[i][sum]++;
			}
		}
		for (int i = ls-1; i > 0; --i) {
			int64 d = s[i] - '0';
			if (i == ls-1) {
				af[i][d]++;
				continue;
			}
			int64 sum = 0;
			for (int j = (1<<(ls-1-i)) - 1; j >= 0; --j) {
				d = s[i] - '0';
				sum = 0;
				for (int k = 0; k < (ls-i-1); ++k) {
					if (j & (1<<k)) {
						d = d * 10 + s[i+k+1] - '0';
					} else {
						sum += d;
						d = s[i+k+1] - '0';
					}
				}
				sum += d;
				af[i][sum]++;

			}
		}
		int ans = 0;
		for (int i = 0; i < ls-1; ++i) {
			MII::iterator it = bf[i].begin();
			for (; it != bf[i].end(); ++it) {
				ans += it->second * af[i+1][it->first];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
