/* Lighted Panels
 * BFS 超时
 * */
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
using namespace std;
const int 
	dx[8] = {-1, -1, -1, 0, 1, 1,  1,  0}, 
	dy[8] = {-1,  0,  1, 1, 1, 0, -1, -1};

#define OPS(ch) ((ch) == '*' ? '.' : '*')

int r, c;
char final_str[65];

int main() {
	int runs;
	scanf("%d", &runs);
	for (int run = 1; run <= runs; ++run) {
		scanf("%d%d", &r, &c);
		char str[65];
		for (int i = 0; i < r; ++i) scanf("%s", str + i * c);
		for (int i = 0; i < r*c; ++i) final_str[i] = '*';
		final_str[r*c] = 0;
		map<string, int> ma;
		queue<string> que;
		ma[str] = 1;
		que.push(str);
		while (!que.empty()) {
			string stat = que.front();
			que.pop();
			int stp = ma[stat];
			for (int i = 0; i < r; ++i) {
				for (int j = 0; j < c; ++j) {
					strcpy(str, stat.c_str());
					str[i*c+j] = OPS(str[i*c+j]);
					for (int k = 0; k < 8; ++k) {
						int x = i + dx[k], y = j + dy[k];
						if (0 <= x && x < r && 0 <= y && y < c) {
							str[x*c+y] = OPS(str[x*c+y]);
						}
					}
					if (ma[str] == 0) {
						que.push(str);
						ma[str] = stp + 1;
						if (strcmp(str, final_str) == 0) {
							goto Answer;
						}
					}
				}
			}
		}
Answer:
		int ans = ma[final_str];
		printf("Case %d: ", run);
		if (ans == 0) puts("impossible");
		else printf("%d\n", ans - 1);
	}
	return 0;
}
