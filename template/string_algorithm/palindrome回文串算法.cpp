/* 回文串Manacher算法
 * 时间复杂度O(n)，空间复杂度O(n)
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// cs 为输入的字符串，从0开始索引，n为字符串长度
// len[i]为以i位置为中心，回文串的半径长度，len数组需要是2*n大小
// 如果i为偶数，则表示以i/2的字符为中心，i为奇数，则以i/2字符和(i+1)/2的字符的中间线为中心
// len[i]表是以i为中心，回文长度是len[i]

void palindrome(char cs[], int len[], int n) {
	memset(len, 0, sizeof(len[0]) * n * 2);
	for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0) ) {
		while (i - j >= 0 && i + j + 1 < n * 2 && cs[(i - j) / 2] == cs[(i + j + 1) / 2]) ++j; /*每次多比较两次*/
		len[i] = j;
		for (k = 1; i - k >= 0 && j - k >= 0 && len[i - k] != j - k; ++k) {
			len[i+k] = min(len[i-k], j - k);
		}
	}
}

void palindrome2(char cs[], int len[], int n) { /* 这个貌似快点,应该是循环少吧，代码也少 */
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

char str[128] = "aabaaab";
int len[256];
void pp(char cs[], int i, int l) {
	printf("%2d:[%2d,%2d] %2d:", i, i/2 - l / 2 + i % 1, i/2 + l/2 + i%2, l);
	for (int j = i/2 - l/2 + i % 1; j <= i/2 + l/2 + i % 1; ++j) printf("%c", cs[j]);
	puts("");
}

void work() {
	int n = strlen(str);
	puts(str);
	palindrome(str, len, n);
	for (int i = 0; i < 2*n; ++i) pp(str, i, len[i]);
	puts("");
	palindrome2(str, len, n);
	for (int i = 0; i < 2*n; ++i) pp(str, i, len[i]);
}
// test palindrome
int main() {
	work();
	while (EOF != scanf("%s", str)) {
		if (strlen(str) == 0) break;
		work();
	}
	return 0;
}
