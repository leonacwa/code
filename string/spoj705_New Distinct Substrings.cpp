/* spoj 705 New Distinct Substrings
 * 后缀数组模板题
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXM = 50005;

int buc[MAXM];
int X[MAXM], Y[MAXM];
int rank[MAXM], height[MAXM], sa[MAXM];

void cal_height(int *r, int n) {
	int i, j, k = 0; // height[i] = LCP(i-1, i)
	//rank[sa[0]] = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i; // sa[0] 是添加的0字符，0字符排第0位，所以可以忽略
	for (i = 0; i < n; height[rank[i++]] = k) // h[i] = height[rank[i]], h[i] >= h[i-1] - 1 
		for (k?k--:0, j = sa[rank[i] - 1]; r[i+k] == r[j+k]; ++k) ;
}

bool cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a+l] == r[b+l];
}

//字符串r末尾是0，所以长度应该是n+1，即原来基础上多加0
void suffix(int *r, int n, int m) {
	int i, l, p, *x = X, *y  = Y, *t;

	for (i = 0; i < m; ++i) buc[i] = 0;
	for (i = 0; i < n; ++i) buc[ x[i] = r[i] ]++;
	for (i = 1; i < m; ++i) buc[i] += buc[i - 1];
	for (i = n - 1; i >= 0; --i) sa[ --buc[x[i]] ] = i;

	for (l = 1, p = 1; p < n; m = p, l <<= 1) {
		for (p = 0, i = n - l; i < n; ++i) y[p++] = i; // 末尾l个子串没有l长的第二关键字
		for (i = 0; i < n; ++i) { // 根据第二关键字，存第一关键字的位置
			if (sa[i] >= l) // 保证有第一关键字
				y[p++] = sa[i] - l; // 记录第一关键字的位置
		}
		for (i = 0; i < m; ++i) buc[i] = 0; //根据第一关键字排序 
		for (i = 0; i < n; ++i) buc[ x[y[i]] ]++;
		for (i = 1; i < m; ++i) buc[i] += buc[i - 1];
		for (i = n - 1; i >= 0; --i) sa[ --buc[ x[y[i]] ] ] = y[i];
		for (t = x, x = y, y = t, x[ sa[0] ] = 0, i = 1, p = 1; i < n; ++i) {//为下次排序准备2*l长的子串的rank值
			x[ sa[i] ] = cmp(y, sa[i-1], sa[i], l) ? p-1 : p++; // 新的rank值
		}
	}
	cal_height(r, n - 1);
}

char str[MAXM];
int num[MAXM];

int main()
{
	int runs;
	scanf("%d\n", &runs);
	while (runs--) {
		gets(str);
		int n = 0;
		for (; str[n]; ++n) {
			num[n] = str[n];
		}
		num[n] = 0;
		suffix(num, n + 1, 128); // 128 是ascii字符集中字符个数
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			ans += n - i - height[rank[i]];
		}
		printf("%d\n", ans);
	}
	return 0;
}

