/* E. Unsolvable
 * */
#include <cstdio>
#include <cstring>

const int NN = 10000000;

bool hasAns[NN + 1000];

void bf() {
	for (int x = 1; x <= NN; ++x) {
		for (int y = 1, t; (t=x/2+y+x*y) <= NN; ++y) {
			hasAns[t] = 1;
			if (t == 255 || t == 1023) {
				printf("%d: %d %d\n", t, x, y);
			}
		}	
	}
	int cnt = 0;
	for (int i = 1; i <= NN; ++i) {
		if (!hasAns[i]) {
			printf("%d ", i);
			++cnt;
			if (cnt == 40) break;
		}
	}
	printf("\n%d\n", cnt);
}

int main() {
	bf();
	return 0;
}
