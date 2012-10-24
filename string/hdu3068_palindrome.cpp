/* HDU 3068 回文串
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 110005;

char str[MAXN];
int len[MAXN * 2];

void palindrome(char cs[], int len[], int n) {
	memset(len, 0, sizeof(len[0])*n*2);
	for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j-k, 0) ) {
		while (i-j >= 0 && i + j + 1 < n*2 && cs[(i-j)/2] == cs[(i+j+1)/2]) ++j;
		len[i] = j;
		for (k = 1; i-k >= 0 && i+k < n*2 && j-k >= 0 && len[i-k] != j-k; ++k) {
			len[i+k] = min(len[i-k], j-k);
		}
	}
}

void palindrome2(char cs[], int len[], int n) {
	for (int i = 0, mx = 0, k, l; i < n * 2; ++i) {
		if (i < mx) l = min(len[k - (i - k)], mx - i);
		else l = 0;
		while (i-l >= 0 && cs[(i-l)/2] == cs[(i+l+1)/2]) ++l;
		len[i] = l;
		if (i + l > mx) {
			mx = i + l;
			k = i;
		}
	}
}


int main() {
	while (EOF != scanf("%s", str)) {
		int n = strlen(str);
		palindrome2(str, len, n);
		int ans = 0;
		for (int i = 0; i < n*2; ++i) {
			if (ans < len[i]) ans = len[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
