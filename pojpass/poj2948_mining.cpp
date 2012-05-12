#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 500 + 2;
int n, m;
int maNorth[NN][NN], maWest[NN][NN], fNorth[NN][NN], fWest[NN][NN];

int main()
{
	while (EOF != scanf("%d %d", &n, &m) && n > 0 && m > 0) {
		memset(maNorth, 0, sizeof(maNorth));
		memset(maWest, 0, sizeof(maWest));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &maWest[i][j]);
				maWest[i][j] += maWest[i][j-1];
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				scanf("%d", &maNorth[i][j]);
				maNorth[i][j] += maNorth[i-1][j];
			}
		}
		memset(fNorth, 0, sizeof(fNorth));
		memset(fWest, 0, sizeof(fWest));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				fNorth[i][j] = maNorth[i][j] + max(fNorth[i][j-1], fWest[i][j-1]);
				fWest[i][j] = maWest[i][j] + max(fWest[i-1][j], fNorth[i-1][j]);
			}
		}
		printf("%d\n", max(fWest[n][m], fNorth[n][m]));
	}
	return 0;
}

