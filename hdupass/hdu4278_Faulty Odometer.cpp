/* HDU 4278 Faulty Odometer
 * 将10进制转成8进制做
 * */
#include <cstdio>
#include <cstring>

int main() {
	char s[12];
	while (EOF != scanf("%s", s) && s[0] != '0') {
		int ans = 0;
		for (int i = 0; s[i]; ++i) {
			int t = s[i] - '0';
			if (t > 8) --t;
			if (t > 3) --t;
			ans = ans * 8 + t;
		}
		printf("%s: %d\n", s, ans);
	}
	return 0;
}
