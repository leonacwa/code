/* City Merger [Fukuoka,2011]
 * http://acm.hnu.cn/online/?action=problem&type=show&id=12525&courseid=0
 * 状态压缩DP
 * 预处理所有字符串，把完全包含在其它串的字符串去掉
 * */
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct Node {
	int s, i;
	Node(){}
	Node(int ts, int ti) : s(ts), i(ti) {}
};

char str[14][21];
char ls[14];
int g[14][14];
int f[1<<14][14];
bool inq[1<<14][14];

int max_eq(char *a, char *b) {
	int s = 0;
	while (*a && *b && *a++ == *b++) ++s;
	return s;
}

int concat(char *a, int la, char *b, int lb) {
	for (; *a; ++a, --la) {
		int r = max_eq(a, b);
		if (r == la || r == lb) {
			return r;
		}
	}
	return 0;
}

int main() {
	int n;
	while (EOF != scanf("%d", &n) && n) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", str[i]);
			ls[i] =  strlen(str[i]);
		}
		int nt = 0;
		for (int i = 0; i < n; ++i) {
			bool can = true;
			for (int j = 0; j < n && can; ++j) {
				if (i != j && strstr(str[j], str[i])) can = false;
			}
			if (can) {
			   	if (nt != i) strcpy(str[nt], str[i]);
				ls[nt] = strlen(str[nt]);
				++nt;
			}
		}
		n = nt;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				g[i][j] = ls[j] - concat(str[i], ls[i], str[j], ls[j]);
			}
		}
		memset(f, -1, sizeof(f));
		memset(inq, 0, sizeof(inq));
		queue<Node> que;
		for (int i = 0; i < n; ++i) {
			f[1<<i][i] = ls[i];
			inq[1<<i][i] = true;
			que.push(Node(1<<i, i));
		}
		while (!que.empty()) {
			Node q = que.front();
			que.pop();
			inq[q.s][q.i] = false;
			for (int i = 0; i < n; ++i) {
				if (q.s & (1<<i)) continue;
				int t = f[q.s][q.i] + g[q.i][i];
				int s = q.s | (1<<i);
				if (f[s][i] == -1 || f[s][i] > t) {
					f[s][i] = t;
					if (!inq[s][i]) {
						que.push(Node(s, i));
						inq[s][i] = true;
					}
				}
			}
		}
		int s = (1<<n) - 1;
		int ans = 99999999;
		for (int i = 0; i < n; ++i) {
			if (f[s][i] != -1 && ans > f[s][i]) ans = f[s][i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
