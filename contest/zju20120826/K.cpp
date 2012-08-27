/* Keep Deleting
 * 栈模拟
 * */
#include <cstdio>
#include <cstring>

const int MAXM = 270, MAXN = 512005;

char t[MAXM], s[MAXN], st[MAXN];

bool cmp(char *s, char *t, int l) {
	--l;
	while (l >= 0 && s[l] == t[l]) --l;
	return l == -1;
}

int main() {
	while (EOF != scanf("%s", t)) {
		scanf("%s", s);
		int top = -1, cnt = 0, lt = strlen(t), ls = strlen(s);
		for (int i = 0; i < ls; ++i) {
			st[++top] = s[i];
			if (top >= lt-1 && st[top] == t[lt-1] && st[top-lt+1] == t[0] && cmp(t, st + top - lt + 1, lt)) {
				++cnt;
				top -= lt;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
