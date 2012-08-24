/* FZU 1894 志愿者选拔
 * 单调队列的题
 * */
#include <cstdio>
#include <cstring>

struct Node {
	int p, r;
} q[1000005];

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		char str[64];
		scanf("%s", str);
		memset(q, 77, sizeof(-1));
		int fr = 0, ta = 0, r, cnt = 0, out = 0;
		while (EOF != scanf("%s", str)) {
			if (str[0] == 'E') break;
			if (str[0] == 'C') {
				++cnt;
				scanf("%s%d", str, &r);
				while (fr < ta && q[ta-1].r < r) --ta;
				q[ta].p = cnt, q[ta].r = r;
				++ta;
			} else if (str[0] == 'G') {
				if (fr < ta) {
					++out;
					while (fr < ta && q[fr].p <= out) ++fr;
				}
			} else if (str[0] == 'Q') {
				if (fr < ta) printf("%d\n", q[fr].r);
				else puts("-1");
			} else {
				while(1);
			}
		}
	}
	return 0;
}
