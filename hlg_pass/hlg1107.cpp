#include <stdio.h>
#include <string.h>

int sn[256];
int kn[256];
char ss[10000+5], ks[256];

int main()
{
	int nCase = 0;
	while (EOF != scanf("%s %s", ss, ks)) {
		memset(sn, 0, sizeof(sn));
		memset(kn, 0, sizeof(kn));
		for (int i = 0; ss[i]; ++i) {
			sn[ss[i]]++;
		}
		for (int i = 0; ks[i]; ++i) {
			kn[ks[i]]++;
		}
		int ans = 10000*3;
		for (int i = 0; ks[i]; ++i) {
			if (ans > sn[ks[i]] / kn[ks[i]]) {
				ans = sn[ks[i]] / kn[ks[i]];
			}
		}
		printf("Case %d: %d\n", ++nCase, ans);
	}
	return 0;
}

