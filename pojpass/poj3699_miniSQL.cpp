/*
 * POJ 3699 miniSQL
 * */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
using namespace std;

const int MAX_N = 10005, MAX_COL = 11;

int col, row;
map<string, int> mt;
char col_name[MAX_COL][1024];
int tp[MAX_COL];

int d_i[MAX_N][MAX_COL];
char *d_s[MAX_N][MAX_COL];
char *sp;
char buf[1<<20];

char str1[1024], str2[1024];

bool cmp(int a, char op, int b) {
	if (op == '=') return a == b;
	else if (op == '<') return a < b;
	return a > b;
}

string itoS(int x) {
	if (x == 0) return string("0");
	char str[32];
	sprintf(str, "%d", x);
	return string(str);
}

void pline(int sz) {
	for (int i = 0; i < sz; ++i) putchar('-');
}
void pstr(const char*s, int sz) {
	int rs = sz - strlen(s), rs2 = rs / 2;
	for (int i = 0; i < rs2; ++i) putchar(' ');
	printf("%s", s);
	for (int i = 0; i < rs2; ++i) putchar(' ');
	if (rs & 1) putchar(' ');
}

int main() {
	int k;
	while (EOF != scanf("%d%d%d", &col, &row, &k)) {
		mt.clear();
		sp = buf;
		for (int i = 0; i < col; ++i) {
			scanf("%s%s", col_name[i], str2);
			mt[col_name[i]] = i;
			tp[i] = str2[0] != 'I';
		}
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				if (tp[j] == 0) {
					int d;
					scanf("%d", &d);
					d_i[i][j] = d;
				} else {
					scanf("%s", sp);
					d_s[i][j] = sp;
					sp += strlen(sp) + 1;
				}
			}
		}
		while (k--) {
			char cn2[1024];
			char op;
			int d, i = 0;
			scanf("%*s %s %*s %s", str1, str2);

			vector<int> lis;
			int nch = 0;
			for (char *ch = str1; ch; ++nch) {
				if (ch[nch] == ',' || ch[nch] == '\0') {
					char rc = ch[nch];
					ch[nch] = 0;
					lis.push_back(mt[ch]);
					ch += nch + 1;
					nch = 0;
					if (rc == '\0') break;
				}
			}

			for (i = 0; str2[i] && str2[i] != '=' && str2[i] != '<' && str2[i] != '>'; ++i) {
				// nothing to do
			}
			op = str2[i];
			str2[i] = 0;
			int c = mt[str2];
			vector<int> vi;
			if (tp[c] == 0) {
				d = atoi(str2 + i + 1);
				for (int x = 0; x < row; ++x) {
					if (cmp(d_i[x][c], op, d)) {
						vi.push_back(x);
					}
				}
			} else {
				strcpy(cn2, str2+i+2);
				cn2[strlen(cn2)-1] = 0;
				for (int x = 0; x < row; ++x) {
					if (strcmp(d_s[x][c], cn2) == 0) vi.push_back(x);
				}
			}

			vector< vector<string> > res;
			int sz = vi.size(), sz2 = lis.size();
			int msz[MAX_COL];
			for (int b = 0; b < sz2; ++b) {
				msz[b] = strlen(col_name[lis[b]]);
			}
			for (int a = 0; a < sz; ++a) {
				vector<string> r;
				for (int b = 0; b < sz2; ++b) {
					if (tp[lis[b]] == 0) {
						r.push_back( itoS(d_i[vi[a]][lis[b]]));
					} else {
						r.push_back(d_s[vi[a]][lis[b]]);
					}
					msz[b] = max(msz[b], (int)r[b].length());
				}
				res.push_back(r);
			}

			int total_sz = sz2 * 3 + 1;
			for (int i = 0; i < sz2; ++i) {
				total_sz += msz[i];
			}
			putchar('+'); pline(total_sz - 2); putchar('+');putchar('\n');
			for (int i = 0; i < sz2; ++i) {
				printf("| ");
				pstr(col_name[lis[i]], msz[i]);
				putchar(' ');
			}
			putchar('|');
			putchar('\n');

			for (int i = 0; i < sz2; ++i) {
				putchar('|'); 
				pline(msz[i] + 2);
			}
			putchar('|');putchar('\n');

			for (int i = 0; i < sz; ++i) {
				for (int j = 0; j < sz2; ++j) {
					printf("| ");
					pstr(res[i][j].c_str(), msz[j]);
					putchar(' ');
				}
				putchar('|');
				putchar('\n');
			}
			putchar('+'); pline(total_sz - 2); putchar('+');putchar('\n');
			puts("");
		}
	}
	return 0;
}
