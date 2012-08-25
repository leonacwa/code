/* The End of The World
 * 汉诺塔问题的变形
 * 给出汉诺塔最优解法时的一个状态，求剩余多少状态
 * */
#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

char str[65];

int64 dfs(char A, char B, char C, int n) {
	if (n == -1) return 0LL;
	if (str[n] == A) return dfs(A, C, B, n-1) + (1LL << n);
	else return dfs(C, B, A, n-1);
}

int main() {
	while (cin >> str) {
		if (str[0] == 'X') break;
		cout << dfs('A', 'B', 'C', strlen(str)-1) << endl;
	}
	return 0;
}
