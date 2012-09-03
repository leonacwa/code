/* LOL
 * 数组越界导致出错
 * */
#include <cstdio>
#include <cstring>

bool find_lxl(const char *s) {
	for (int i = 0; s[i]; ++i) { // 判断结束的时候越界了，导致出错
		if (s[i] == 'l' && s[i+2] == 'l' && s[i+1] != '\0') return true;
	}
	return false;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int ans;
		char str[65];
		scanf("%s", str);
		if (strstr(str, "lol")) {
			ans = 0;
		} else if (strstr(str, "lo") || strstr(str, "ol") || strstr(str, "ll") || find_lxl(str)) {
			ans = 1;
		} else if (strchr(str, 'l') || strchr(str, 'o')) {
			ans = 2;
		} else {
			ans = 3;
		}
		printf("%d\n", ans);
	}
	return 0;
}
