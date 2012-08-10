/* Youth Hostel Dorm
 * 贪心法 + 构造
 * */
#include <cstdio>
#include <cstring>

const int MaxN = 9;
char m[MaxN][MaxN], m2[MaxN][MaxN];
int ans[MaxN][MaxN];

void init(char m[][MaxN], int l, int w) {
	for (int i = 0; i < l; ++i) {
		memset(m[i], '.', sizeof(char) * w);
		m[i][w] = 0;
	}
}

void go(char m[][MaxN], int l, int w, int f, int dep) {
	for (int i = 0; i < l; ++i) {
		if (f) m[i][w-1] = 'B'; else m[w-1][i] = 'B';
	}
	for (int i = 0; i < w - 2; ++i) {
		if (f) m[l-1][i] = 'B'; else m[i][l-1] = 'B';
	}
	for (int i = 0; i < w; ++i) {
		char ch = 'B';
		if ((w - i) % 3 == 2) ch = '.';
		for (int j = 0; j < l - 2; ++j) {
			if (f) m[j][i] = ch; else m[i][j] = ch;
		}
	}
	if (w % 3 && (w > 5 || l > 5)) go(m, 3 + w % 3, l, !f, dep+1);
	if (dep == 0) {
		if (f) m[l-1][w-2] = 'E'; else m[w-2][l-1] = 'E';
		if (m[0][0] == 'B' && m[0][1] == 'B' && m[1][0] == 'B') m[0][0] = '.';
		if (m[1][0] == 'B' && m[2][0] == 'B' && m[0][1] == 'B') m[1][0] = '.';
		if (m[0][1] == 'B' && m[0][2] == 'B' && m[1][0] == 'B') m[0][1] = '.';
	}
}

int count_mat(char m[][MaxN], int l, int w) {
	int s = 0;
	for (int i = 0; i < l; ++i) {
		for (int j = 0; j < w; ++j) {
			if (m[i][j] == 'B') ++s;
		}
	}
	return s;
}

int main() {
	int runs;
	scanf("%d", &runs);
	while (runs--) {
		int l, w;
		scanf("%d%d", &l, &w);
		if (l == 1 && w == 1) {
			m[0][0] = 'E';
			m[0][1] = 0;
		} else if (l == 1) {
			m[0][0] = 'B', m[0][1] = 'E', m[0][2] = 'B', m[0][w] = 0;
			for (int i = 3; i < w; ++i) m[0][i] = '.';
		} else if (w == 1) {
			m[0][0] = 'B', m[0][1] = 0;
			m[1][0] = 'E', m[1][1] = 0;
			m[2][0] = 'B', m[2][1] = 0;
			for (int i = 3; i < l; ++i) m[i][0] = '.', m[i][1] = 0;
		} else if (l == 2 && w != 3) {
			m[0][0] = 'E';
			m[1][0] = 'B';
			for (int i = 1; i < w; ++i) m[0][i] = '.', m[1][i] = 'B';
			m[0][w] = 0;
			m[1][w] = 0;
		} else if (w == 2 && l != 3) {
			m[0][0] = 'E', m[0][1] = 'B', m[0][2] = 0;
			for (int i = 1; i < l; ++i) m[i][0] = '.', m[i][1] = 'B', m[i][2] = 0;
		} else if (l == 3) {
			for (int i = 0; i < w; ++i) m[0][i] = m[2][i] = 'B';
			m[0][w] = m[2][w] = 0;
			m[1][0] = 'E', m[1][w] = 0;
			for (int i = 1; i < w; ++i) m[1][i] = '.';
		} else if (w == 3) {
			for (int i = 0; i < l; ++i) m[i][0] = m[i][2] = 'B', m[i][1] = '.', m[i][3] = 0;
			m[0][1] = 'E';
		} else {
			init(m, l, w);
			init(m2, l, w);
			go(m, l, w, 1, 0);
			go(m2, w, l, 0, 0);
			if (count_mat(m, l, w) < count_mat(m2, l, w)) {
				for (int i = 0; i < l; ++i) {
					for (int j = 0; j < w; ++j) {
						m[i][j] = m2[i][j];
					}
					m[i][w] = 0;
				}
			}
		}
		ans[l-1][w-1] = count_mat(m, l, w);
	//	printf("\nsize %d %d, %d\n", l, w, count_mat(m, l, w));
		for (int i = 0; i < l; ++i) puts(m[i]); // AC
		//for (int i = 0; i < l; ++i) printf(m[i]); // PE
	}
	/*
	puts("{");
	for (int i = 0; i < 8; ++i) {
		printf("{%d", ans[i][0]);
		for (int j = 1; j < 8; ++j) {
			printf(", %d", ans[i][j]);
		}
		if (i + 1 < 8) puts("},");
		else puts("}");
	}
	puts("}");
	*/
	return 0;
}
