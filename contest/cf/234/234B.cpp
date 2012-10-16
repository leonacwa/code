/*
 * CF 234 B. Reading
 * */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 1005;
int idx[MAXN];
int level[MAXN];

bool cmp_idx(const int &i, const int &j) {
	return level[i] > level[j];
}

int main() {	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%d", level + i);
		idx[i] = i;
	}
	sort(idx, idx + n, cmp_idx);
	printf("%d\n", level[idx[k-1]]);
	sort(idx, idx+k);
	for (int i = 0; i < k-1; ++i) {
		printf("%d ", idx[i] + 1);
	}
	printf("%d\n", idx[k-1]+1);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
