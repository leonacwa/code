/*
 * CF 239 B. Easy Tape Programming
 * */
#include <cstdio>
#include <cstring>

bool isLR(char ch) {
	return ch == '<' || ch == '>';
}

int main() {
	int n, q;
	char str[256];
	while (EOF != scanf("%d%d", &n, &q)) {
		scanf("%s", str);
		while (q--) {
			int l, r, len;
			int cnt[10] = {0};
			bool is[256] = {0};
			char op[256];
			scanf("%d%d", &l, &r);
			--l, --r;
			len = r - l + 1;
			for (int i = 0; i+l <= r; ++i) {
				op[i] = str[i+l];
				is[i] = 1;
			}
			int cp = 0, dp = 1, pre = len;
			while (cp >= 0 && cp < len) {
				if (is[cp]) {
					if (isLR(op[cp])) {
						if (is[pre] && isLR(op[pre])) {
							is[pre] = 0;
						}
						if (op[cp] == '<') dp = -1;
						else dp = 1;
					} else {
						cnt[ op[cp] - '0' ]++;
						if (op[cp] == '0') {
							is[cp] = 0;
						} else {
							op[cp]--;
						}
					}
					pre = cp;
					cp += dp;
				} else {
					cp += dp;
				}
			}
			for (int i = 0; i < 9; ++i) {
				printf("%d ", cnt[i]);
			}
			printf("%d\n", cnt[9]);
		}
	}
	return 0;
}
