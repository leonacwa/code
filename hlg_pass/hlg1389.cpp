#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 1000000 + 100;
struct JiaozhuV5 {
	int pos, left, right;
};
JiaozhuV5 jv[NN];
char s[NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int k, cnt, ls;
		scanf("%d\n%s", &k, s);
		ls = 0;
		cnt = 0;
		for (int i = 0; s[i]; ++i) {
			++ls;
			if ('J' == s[i] && 'i' == s[i+1] && 'a' == s[i+2] && 'o' == s[i+3] && 
					'z' == s[i+4] && 'h'== s[i+5] && 'u' == s[i+6] && 'V' == s[i+7] && '5' == s[i+8]) {
				jv[cnt].pos = i;
				jv[cnt].left = cnt == 0 ? i : i - (jv[cnt-1].pos + 9);
				if (cnt > 0) {
					jv[cnt-1].right = i - (jv[cnt-1].pos + 9);
				}
				++cnt;
			}
		}
		if (cnt > 0) {
			jv[cnt-1].right = ls - (jv[cnt-1].pos + 9);
		}
		long long ans = 0, t;
		//printf("cnt:%d\n", cnt);
		if (cnt == 0 && k == 0) {
			t = strlen(s);
			ans = (t + 1) * t / 2;
		} else if (k == 0) {
			t = jv[0].pos + 8;
			ans += (t + 1) * t / 2;
			for (int i = 1; i < cnt; ++i) {
				t = jv[i].pos - jv[i-1].pos + 7;
				ans += (t + 1) * t / 2 - 8 * 7 / 2;
			}
			t = ls - jv[cnt-1].pos - 1;
			ans += (t + 1) * t / 2 - 8 * 7 / 2;
		} else if (0 < k && k-1 < cnt) {
			for (int i = 0; i+k-1 < cnt; ++i) {
				ans += (jv[i].left + 1LL + (i == 0 ? 0: 8)) * (jv[i+k-1].right + 1LL + (i+k == cnt ? 0 : 8));
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

