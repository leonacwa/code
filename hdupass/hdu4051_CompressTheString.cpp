/* 搜索+剪枝
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 4, MAXL = 4, MAXLEN = 505;
char S[MAXLEN];
int s[MAXN][MAXL];
int N, L[MAXN], ls[MAXN], lss[MAXN], lens, start[MAXN];
bool C[MAXN];

bool check() // 检查一组解，从s[0]开始，也就是题目的s[1]
{
	C[0] = C[1] = C[2] = C[3] = false;
	C[0] = true;
	start[0] = 0;
	for (int k = 0; k < N-1; ++k) {
		if (C[k]) {
			int p = start[k];
			for (int i = 0; i < ls[k]; ++i) {
				int v = s[k][i];
				if (v == N) {
					++p;
				} else {
					if (C[v]) { // 再次用到short str v，那么就应该有匹配的相等
						for (int j = 0; j < lss[v]; ++j) {
							if (S[start[v]+j] != S[p+j]) return false;
						}
					} else {
						C[v] = true;
						start[v] = p;
					}
					p += lss[v]; // shit! 错这里了，填成lss[k]了
				}
			}
		}
	}
	return true;
}

bool dfs1(int, int);
bool dfs2(int, int, int);

bool dfs2(int k, int i, int max_ll)
{
	if (lss[k] > lens) return false;
	if (k == 0 && (lss[0]+(i+1)*max_ll < lens || lss[0] +(i+1) > lens)) return false; // 这个剪枝立竿见影
	if (i == -1) {
		return dfs1(k-1, max(max_ll, lss[k]));
	} else {
		//for (s[k][i] = k+1; s[k][i] <= N; ++s[k][i]) {
		for (s[k][i] = N; s[k][i] >= k+1; --s[k][i]) {//枚举第k个short str i位置的值,可以取short str 或者非shortstr
			int t = s[k][i] == N ? 1 : lss[s[k][i]];
			lss[k] += t;
			if (dfs2(k, i-1, max_ll)) return true;
			lss[k] -= t;
		}
	}
	return false;
}

bool dfs1(int k, int max_ll)
{
	//if (max_ll > lens) return false;
	int t = max_ll;
	for (int i = k; i >= 0; --i) t *= L[i];
	if (t < lens) return false; // 最大长度剪枝
	if (k == -1) {
		if (lss[0] == lens) return check();
	} else {
		for (ls[k] = L[k]; ls[k] > 0; --ls[k]) { // 枚举第k个short str 的长度 
			lss[k] = 0;
			if (dfs2(k, ls[k]-1, max_ll)) return true;
		}
	}
	return false;
}

int main()
{
	while (EOF != scanf("%d", &N)) {
		for (int i = 0; i < N; ++i) scanf("%d", &L[i]);
		scanf("%s", S);
		lens = strlen(S);
		int maxlen = L[N-1];
		for (int i = N-2; i >= 0; --i) maxlen *= L[i];
		bool yes = false;
		if (maxlen >= lens) yes = dfs1(N-1, 1);
		puts(yes ? "Yes" : "No");
}
	return 0;
}

