#include <cstdio>
#include <iostream>
using namespace std;

const int NN = 100 + 5;
int mm[NN][NN];
int n, m;

int main()
{
	while (EOF != scanf("%d %d", &n, &m)) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &mm[i][j]);
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (mm[i][j] == 1) {
					for (int ii = 1; i + ii < n; ++ii) {
						if (mm[i+ii][j] == 1) {
							for (int jj = 1; j + jj < m; ++jj) {
								if (mm[i][j+jj] == 1 && mm[i+ii][j+jj] == 1) {
									++ans;
								}
							}
						}
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

