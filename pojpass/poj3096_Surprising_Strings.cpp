#include <stdio.h>
#include <string.h>

int main()
{
	char str[80];
	while (EOF != scanf("%s", str) && str[0] != '*') {
		int len = strlen(str);
		bool surprise = true;
		for (int step = 0; step+1 < len; step++) {
			int cnt[26][26] = {0};
			for (int i = 0; i+step+1 < len; i++) {
				int a = str[i] - 'A', b = str[i+step+1] - 'A';
				cnt[a][b]++;
				if (cnt[a][b] > 1) {
					surprise = false;
					break;
				}
			}
			if (surprise == false) {
				break;
			}
		}
		printf("%s is%ssurprising.\n", str, surprise?" ":" NOT ");
	}
	return 0;
}

