/* Sudoku
 * 深搜，回溯
 * */
#include <cstdio>
#include <cstring>

const int term[6][3] = {
	{0, 1, 2},
	{0, 2, 1},
	{1, 0, 2},
	{1, 2, 0},
	{2, 0, 1},
	{2, 1, 0}
};

int b1[9][9], b2[9][9];
const int *colseg, *rowseg;
const int *col[3];

bool swap_row(int r, int m[]);

bool check_row(int r, const int p[], int m[]) {
	int m2[10];
	memcpy(m2, m, sizeof(m[0])*10);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			for (int k = 0; k < 3; ++k) {
				int r1 = 3 * rowseg[r] + p[i], c1 = 3 * colseg[j] + col[j][k], r2 = 3*r + i, c2 = 3*j + k;
				int v1 = b1[r1][c1], v2 = b2[r2][c2];
				if (v2) {
					if (m2[v2] == -1) {
						m2[v2] = v1;
					} else if (m2[v2] != v1) {
						return false;
					}
				}
			}
		}
	}
	return swap_row(r+1, m2);
}
bool swap_row(int r, int m[]) {
	if (r == 3) return true;
	for (int i = 0; i < 6; ++i) {
		if (check_row(r, term[i], m)) return true;
	}
	return false;
}

bool swap_col() {
	int m[10];
	memset(m, -1, sizeof(m[0])*10);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			for (int k = 0; k < 6; ++k) {
				col[0] = term[i], col[1] = term[j], col[2] = term[k];
				if (swap_row(0, m)) return true;
			}
		}
	}
	return false;
}

bool swap_seg() {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			rowseg = term[i];
			colseg = term[j];
			if (swap_col()) return true;
		}
	}
	return false;
}

bool solve() {
	if (swap_seg()) return true;
	int b[9][9];
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			b[i][j] = b1[j][8-i]; // clockwise
			//b[i][j] = b1[8-j][i];
		}
	}
	memcpy(b1, b, sizeof(b1[0][0])*81);
	return swap_seg();
}

void read_board(int b[9][9]) {
	char str[32];
	for (int i = 0; i < 9; ++i) {
		scanf("%s", str);
		for (int j = 0; j < 9; ++j) b[i][j] = str[j] - '0';
	}
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		read_board(b1);
		read_board(b2);
		puts(solve() ? "Yes" : "No");
	}
	return 0;
}
