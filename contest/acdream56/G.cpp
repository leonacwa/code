/* Here Be Dragons!
 * */
#include <cstdio>
#include <cstring>

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		char str[64];
		scanf("%s", str);
		if (strchr(str, 'D')) puts("You shall not pass!");
		else puts("Possible");
	}
	return 0;
}
