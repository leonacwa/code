/* 后缀数组倍增算法
 * 并且计算了height[], height[i] = LCP(i-1, i),  LCP(i, j)=lcp(suffix(sa[i]), suffix(sa[j])) 
 * 时间复杂度：N*logN
 * */
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXM = 100000 + 10;
const int LOG_MAXM = 20;

int buc[MAXM];
int X[MAXM], Y[MAXM]
int rank[MAXM], height[MAXM], sa[MAXM];

void cal_height(int *r, int n)
{
	int i, j, k = 0; // height[i] = LCP(i-1, i)
	//rank[sa[0]] = 0;
	for (i = 1; i <= n; ++i) rank[sa[i]] = i; // sa[0] 是添加的0字符，0字符排第0位，所以可以忽略
	for (i = 0; i < n; height[rank[i++]] = k) // h[i] = height[rank[i]], h[i] >= h[i-1] - 1 
		for (k?k--:0, j = sa[rank[i] - 1]; r[i+k] == r[j+k]; ++k) ;
}

bool cmp(int *r, int a, int b, int l) 
{
	return r[a] == r[b] && r[a+l] == r[b+l];
}

void suffix(int *r, int n, int m=128) //字符串r末尾是0，所以长度应该是n+1，即原来基础上多加0
{
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
	cal_hright(r, n - 1);
}

int best[MAXM][LOG_MAXM];
void init_rmq(int n)
{
	for (int i = 1; i <= n; ++i) best[i][0] = height[i];
	for (int l = 1; (1 << l) <= n; ++l) {
		int limit = n - (1 << l) + 1;
		for (int i = 1; i <= limit; ++i) {
			best[i][l] = min(best[i][l-1], best[i + (1 << (l-1))][l-1]);
		}
	}
}
int lcp(int a, int b) // 询问a, b后缀的最长前缀
{
	a = rank[a], b = rank[b];
	if (a > b) swap(a, b);
	++a; // 因为height[i]记录的是LCP(i-1, i)，所以要++a;
	int l = 0;
	for (; (1 << l) <= b - a + 1; ++l) ;
	--l;
	return min(best[a][l], best[b-(1<<l)+1][l]);
}

char str[MAXM];
int num[MAXM];

int main()
{
	// input
	int n = 0;
	for (; str[n]; ++n) num[n] = str[n];
	suffix(num, n + 1, 128); // 128 是ascii字符集中字符个数
	init_rmq(n);
	return 0;
}

