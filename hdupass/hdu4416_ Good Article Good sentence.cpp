/* HDU 4416  Good Article Good sentence
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int64;

const int MAXN = 300005;
const int LOG_MAXN = 19;

struct SuffixArray {
	int n;
	int buc[MAXN];
	int X[MAXN], Y[MAXN];
	int rank[MAXN], height[MAXN], sa[MAXN];

	int best[MAXN][LOG_MAXN];

	bool cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a+l] == r[b+l];
	}

	//字符串r末尾是0，所以长度应该是n+1，即原来基础上多加0
	void init(int *r, int n, int m=128) {
		this->n = n;
		r[n] = 0;
		int i, l, p, *x = X, *y  = Y, *t;

		for (i = 0; i < m; ++i) buc[i] = 0;
		for (i = 0; i <= n; ++i) buc[ x[i] = r[i] ]++;
		for (i = 1; i < m; ++i) buc[i] += buc[i - 1];
		for (i = n; i >= 0; --i) sa[ --buc[x[i]] ] = i;

		for (l = 1, p = 1; p <= n; m = p, l <<= 1) {
			for (p = 0, i = n+1 - l; i <= n; ++i) y[p++] = i; // 末尾l个子串没有l长的第二关键字
			for (i = 0; i <= n; ++i) { // 根据第二关键字，存第一关键字的位置
				if (sa[i] >= l) // 保证有第一关键字
					y[p++] = sa[i] - l; // 记录第一关键字的位置
			}
			for (i = 0; i < m; ++i) buc[i] = 0; //根据第一关键字排序 
			for (i = 0; i <= n; ++i) buc[ x[y[i]] ]++;
			for (i = 1; i < m; ++i) buc[i] += buc[i - 1];
			for (i = n; i >= 0; --i) sa[ --buc[ x[y[i]] ] ] = y[i];
			for (t = x, x = y, y = t, x[sa[0]] = 0, i = 1, p = 1; i <= n; ++i) {//为下次排序准备2*l长的子串的rank值
				x[ sa[i] ] = cmp(y, sa[i-1], sa[i], l) ? p-1 : p++; // 新的rank值
			}
		}
		int j, k = 0;
		// height[i] = LCP(i-1, i)
		//rank[sa[0]] = 0;
		for (i = 1; i <= n; ++i) rank[sa[i]] = i; // sa[0] 是添加的0字符，0字符排第0位，所以可以忽略
		for (i = 0; i < n; height[rank[i++]] = k) // h[i] = height[rank[i]], h[i] >= h[i-1] - 1 
			for (k?k--:0, j = sa[rank[i] - 1]; r[i+k] == r[j+k]; ++k) ;
	}

	void init_rmq() {
		for (int i = 1; i <= n; ++i) best[i][0] = height[i];
		for (int l = 1; (1 << l) <= n; ++l) {
			int limit = n - (1 << l) + 1;
			for (int i = 1; i <= limit; ++i) {
				best[i][l] = min(best[i][l-1], best[i + (1 << (l-1))][l-1]);
			}
		}
	}
	// 询问排名为a  b的最长前缀长度
	int LCP(int a, int b) {
		if (a > b) swap(a, b);
		++a; // 因为height[i]记录的是LCP(i-1, i)，所以要++a;
		int l = 0;
		for (; (1 << l) <= b - a + 1; ++l) ;
		--l;
		return min(best[a][l], best[b-(1<<l)+1][l]);
	}
	// 询问字符串a, b后缀的最长前缀长度
	int lcp(int a, int b) {
		a = rank[a], b = rank[b];
		return LCP(a, b);
	}
};
SuffixArray sa;
char str[MAXN];
int num[MAXN];

int main() {
	int runs;
	scanf("%d", &runs);
	for (int ca = 1; ca <= runs; ++ca) {
		int n;
		scanf("%d", &n);
		scanf("%s", str);
		int la = 0, len = 0;
		for (; str[la]; ++la) num[la] = str[la];
		num[la] = 127;
		len = la + 1;
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			for (int j = 0; str[j]; ++j) num[len++] = str[j];
			num[len++] = 128 + i;
		}
		sa.init(num, len, 128+n);
		sa.init_rmq();
		int64 ans = 0;
		int b = 1, t;
		for (int i = 1; i <= len; ++i) {
			if (sa.sa[i] >= la) continue;
			while (b <= len && (b <= i || sa.sa[b] <= la)) ++b;
			if (b <= len) t = max(sa.height[i], sa.LCP(i, b));
			else t = sa.height[i];
			ans += la - sa.sa[i] - t;
		}
		printf("Case %d: %lld\n", ca, ans);
	}
	return 0;
}
