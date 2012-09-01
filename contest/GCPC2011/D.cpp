/* Magic Star
 * http://www.spoj.pl/problems/GCPC11D/
 * */
#include <cstdio>
#include <cstring>
#include <cstdlib>

int cnt[5][27];
int mat[10][10];

struct Point {
	int x, y;
};

const int star[6][4][2] = {
	{{1, 1}, {1, 3}, {1, 5}, {1, 7}},
	{{3, 1}, {3, 3}, {3, 5}, {3, 7}},
	{{0, 4}, {1, 3}, {2, 2}, {3, 1}},
	{{0, 4}, {1, 5}, {2, 6}, {3, 7}},
	{{1, 1}, {2, 2}, {3, 3}, {4, 4}},
	{{1, 7}, {2, 6}, {3, 5}, {4, 4}},
};

Point list[13];
int list_size;
int num[13], num_cnt;
bool used[13];

void print_mat();

bool check() {
	for (int i = 0; i < 6; ++i) {
		int sum = 0, pt = 0;
		for (int j = 0; j < 4; ++j) {
			int x = star[i][j][0], y = star[i][j][1];
			if (mat[x][y] > 0) {
				sum += mat[x][y];
				++pt;
			}
		}
		if (sum>26 || (sum<26&&pt==4) || (sum==26&&pt<4) || (sum<26&&cnt[4-pt][26-sum]==0)) {
			/*
			   printf("check %d: %d %d %d\n", i, sum, pt, cnt[4-pt][26-sum]);
			   for (int j = 0; j < 4; ++j) {
			   int x = star[i][j][0], y = star[i][j][1];
			   printf("%d ", mat[x][y]);
			   }
			   puts("");
			   print_mat();
			   */
			return false;
		}
	}
	return true;
}

void deal(int i, int v) {
	int ni = num[i];
	cnt[1][ni] += v;
	for (int j = 0; j < num_cnt; ++j) {
		int nj = num[j];
		if (cnt[1][nj] == 0 || ni+nj > 26) continue;
		cnt[2][ni + nj] += v;
		for (int k = j+1; k < num_cnt; ++k) {
			int nk = num[k];
			if (cnt[1][nk] == 0 || ni+nj+nk > 26) continue;
			cnt[3][ni + nj + nk] += v;
			for (int l = k+1; l < num_cnt; ++l) {
				int nl = num[l];
				if (cnt[1][nl] == 0 || ni+nj+nk+nl > 26) continue;
				cnt[4][ni + nj + nk + nl] += v;
			}
		}
	}
}

bool dfs(int a) {
	if (a == list_size) {
		return true;
	}
	int x = list[a].x, y = list[a].y;
	for (int i = 0; i < num_cnt; ++i) {
		if (cnt[1][num[i]] == 0) continue;
		if (mat[x][y] != 0) {
			//	printf("%d: %d %d, %d\n", a, x, y, mat[x][y]);
			while(1);
			exit(-1);
		}
		mat[x][y] = num[i];
		deal(i, -1);
		//printf("%d: %d %d, %d\n", a, x, y, num[i]);
		if (check()) {
			if (dfs(a+1)) return true;
		}
		//puts("");
		mat[x][y] = 0;
		deal(i, 1);
	}
	return false;
}

void print_mat() {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 9; ++j) {
			if(mat[i][j] == 0) putchar('.');
			else putchar(mat[i][j] + 'A' - 1);
		}
		putchar('\n');
	}
	//putchar('\n');
}

void print_p() {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			printf("(%d, %d) ", star[i][j][0], star[i][j][1]);
		}
		puts("");
	}
	puts("");
}

void init() {
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= 12; ++i) {
		if (used[i]) continue;
		cnt[1][i]++;
		for (int j = i+1; j <= 12; ++j) {
			if (used[j]) continue;
			cnt[2][i+j]++;
			for (int k = j+1; k <= 12; ++k) {
				if (used[k]) continue;
				if (i+j+k > 26) break;
				cnt[3][i+j+k]++;
				for (int l = k+1; l <= 12; ++l) {
					if (used[l]) continue;
					if (i+j+k+l > 26) break;
					cnt[4][i+j+k+l]++;
				}
			}
		}
	}
}

int main() {
	//print_p();
	char str[32];
	while (gets(str)) {
		list_size = 0;
		memset(mat, 0, sizeof(mat));
		memset(used, 0, sizeof(used));
		num_cnt = 12;
		for (int i = 1; i <= 12; ++i) {
			num[i-1] = i;
		}
		for (int i = 0; i < 5; ++i) {
			if (i > 0) gets(str);
			for (int j = 0; j < 9; ++j) {
				if (str[j] == 'x') {
					list[list_size].x = i;
					list[list_size].y = j; 
					++list_size;
				} else if ('A' <= str[j] && str[j] <= 'L') {
					int t = str[j] - 'A' + 1;
					mat[i][j] = t;
					used[t] = true;
				} else {
					while (str[j] != '.') ;
				}
			}
			str[0] = 0;
		}
		num_cnt = 0;
		for (int i = 1; i <= 12; ++i) {
			if (!used[i]) {
				num[num_cnt++] = i;
			}
		}
		init();
		while (!dfs(0)) break;
		print_mat();
	}
	return 0;
}
