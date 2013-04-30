/*
 * CF 259 B. Little Elephant and Magic Square
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ma[3][3];

#define IN_RANGE(x) (0<(x)&&(x)<=1e5+0.1)

bool check() {
	if (!IN_RANGE(ma[0][0]) || !IN_RANGE(ma[1][1]) || !IN_RANGE(ma[2][2])) return 0;
	int sum = ma[0][0] + ma[0][1] + ma[0][2];
	if (sum != ma[0][0]+ma[1][1]+ma[2][2] || sum != ma[0][2]+ma[1][1]+ma[2][0]) return 0;
	for (int i = 0; i < 3; ++i) {
		if (sum != ma[i][0] + ma[i][1] + ma[i][2]) return 0;
		if (sum != ma[0][i] + ma[1][i] + ma[2][i]) return 0;
	}
	return 1;
}

void print() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			printf("%d ", ma[i][j]);
		}
		printf("%d\n", ma[i][2]);
	}

}

int main() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			scanf("%d", &ma[i][j]);
		}
	}
	if (ma[0][2] == 0 && ma[2][0] == 0) {
		for (int i = 0; i < 3; ++i) {
			swap(ma[i][0], ma[i][2]);
		}
	}
	bool can = false;
	for (int i = 1; i <= 1e5+0.1; ++i) {
		ma[0][0] = i;
		int sum = ma[0][0] + ma[0][1] + ma[0][2];
		ma[1][1] = sum - ma[1][0] - ma[1][2];
		ma[2][2] = sum - ma[2][0] - ma[2][1];
		if (check()) {
			can = true;
		//	puts("can");
			break;
		}
	}
	print();
	return 0;
}
