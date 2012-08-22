#include <stdio.h>

int main()
{
	int n;
	while (EOF != scanf("%d", &n) && n > 0) {
		char str[32];
		int cnt[256] = {0};
		scanf("%s", str);
		for (int i = 0; i < n; i++) {
			cnt[str[i]]++;
		}
		for (int i = 0; i < 10; i++) {
			if (cnt['a'+i] >= 3) {
				n -= cnt['a'+i];
				cnt['a'+i] = 0;
			}
			if (cnt['A'+i] >= 3) {
				n -= cnt['A'+i];
				cnt['A'+i] = 0;
			}
		}
		for (int i = 0; i < 10; i++) {
			bool change = false;
			if (cnt['a'+i] >= 1 && cnt['A'+i] >= 2) {
				cnt['a'+i] -= 1;
				cnt['A'+i] -= 2;
				n -= 3;
				change = true;
			}
			if (cnt['a'+i] >= 2 && cnt['A'+i] >= 1) {
				cnt['a'+i] -= 2;
				cnt['A'+i] -= 1;
				n -= 3;
				change = true;
			}
			if (cnt['a'+i] >= 1 && cnt['a'+i+1] >= 1 && cnt['a'+i+2] >= 1) {
				cnt['a'+i]--;
				cnt['a'+i+1]--;
				cnt['a'+i+2]--;
				n -= 3;
				change = true;
			}
			if (cnt['A'+i] >= 1 && cnt['A'+i+1] >= 1 && cnt['A'+i+2] >= 1) {
				cnt['A'+i]--;
				cnt['A'+i+1]--;
				cnt['A'+i+2]--;
				n -= 3;
				change = true;
			}
			if (change) {
				i = i-1;
			}
		}
		if (n != 0 ) {
			printf("No\n");
		} else {
			printf("Yes\n");
		}
	}
	return 0;
}

