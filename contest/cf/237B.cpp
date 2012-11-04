/*
 * CF 237 B. Young Table
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> va[2505], vb[2505], op[2505][2];

int mat[64][64];

int main() {
	int n;
	int c[64];
	while (EOF != scanf("%d", &n)) {
		int s = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
		for (int i = 1; i <= n; ++i) {
			s += c[i];
			for (int j = 1, v; j <= c[i]; ++j) {
				scanf("%d", &v);
				va[v] = make_pair(i, j);
				mat[i][j] = v;
			}
		}
		int k = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= c[i]; ++j) {
				++k;
				vb[k] = make_pair(i, j);
			}
		}
		int cnt = 0;
		for (int i = 1; i <= s; ++i) {
			if (va[i] != vb[i]) {
				int b = mat[vb[i].first][vb[i].second];
				while (va[i] == vb[i]);
				op[cnt][0] = va[i];
				op[cnt++][1] = vb[i];
				mat[va[i].first][va[i].second] = b;
				mat[vb[i].first][vb[i].second] = i;
				swap(va[b], va[i]);
			}
		}
		printf("%d\n", cnt);
		for (int i = 0; i < cnt; ++i) {
			printf("%d %d %d %d\n", op[i][0].first, op[i][0].second, op[i][1].first, op[i][1].second);
		}
	}
	return 0;
}
