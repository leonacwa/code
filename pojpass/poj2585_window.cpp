#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const char cover[4][4][5] = {
	{"1", "12", "23", "3"},
	{"14", "1245", "2356", "36"},
	{"47", "4578", "5689", "69"},
	{"7", "78", "89", "9"}
};

bool mat[10][10];
bool show[10];
int id[10];

int main()
{
	char s[16];
	scanf("%s", s);
	while (0 != strcmp(s, "ENDOFINPUT")) {
		memset(show, 0, sizeof(show));
		memset(mat, 0, sizeof(mat));
		memset(id, 0, sizeof(id));
		int tot = 0;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				int d;
				scanf("%d", &d);
				--d;
				if (!show[d]) {
					show[d] = true;
					++tot;
				}
				for (const char *c = cover[i][j]; *c; ++c) {
					if (*c != '1' + d && mat[d][*c - '1'] == false) {
						mat[d][*c - '1'] = true;
						id[*c - '1']++;
					}
				}
			}
		}
		bool can = true;
		for (int k = 0; k < tot; ++k) {
			int i = 0;
			while (!show[i] || (i < 9 && id[i] > 0)) {
				++i;
			}
			if (i >= 9) {
				can = false;
				break;
			}
			show[i] = false;
			for (int j = 0;j < 9; ++j) {
				if (mat[i][j]) {
					--id[j];
				}
			}
		}
		printf("%s\n", can ? "THESE WINDOWS ARE CLEAN" : "THESE WINDOWS ARE BROKEN");
		scanf("%s", s);
		scanf("%s", s);
	}
	return 0;
}

