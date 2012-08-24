#include <stdio.h>
int h[30000+12];
int dp[30000+12];

int main()
{
	int n, i, j, k, t, Min, num;
	while (EOF != scanf("%d", &n)) {
		for (i = 0; i < n; ++i) {
			scanf("%d", h+i);
		}
		num = 1;
		dp[0] = h[0];
		for (i = 1; i < n; ++i) {
			Min = 30000*2;
			k = -1;
			for (j = 0; j < num; ++j) {
				t = dp[j] - h[i];
				if (t >= 0 && t < Min) {
					k = j;
					Min = t;
				}
			}	
			if (k == -1) {
				dp[num++] = h[i];
			}
			else {
				dp[k] = h[i];
			}
		}
		printf("%d\n", num);
	}
	return 0;
}

