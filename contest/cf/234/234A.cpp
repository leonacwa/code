/*
 * CF 234 A. Lefthanders and Righthanders
 * */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

const int MAXN = 105;

char str[MAXN];
int n;

int main() {
	freopen("input.txt", "r", stdin);	freopen("output.txt", "w", stdout);
	scanf("%d%s", &n, str);
	n >>= 1;
	for (int i = 0; i < n; ++i) {
		int a = i, b = i + n;
		if (str[a] == 'R' && str[b] == 'L') swap(a, b);
		printf("%d %d\n", a+1, b+1);
	}
	fclose(stdin);	fclose(stdout);
	return 0;
}
