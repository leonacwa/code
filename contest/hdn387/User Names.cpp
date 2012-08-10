#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <map>
using namespace std;

char s[128*3], t[128*3];
map<string, bool> db;
map<string, bool>::iterator it;

int main()
{
	int nCase = 0, n, max_len, i, j, k, p, d, ls;
	while (EOF != scanf("%d %d\n", &n, &max_len) && n != 0 && max_len != 0) {
		db.clear();
		//printf("input : %d %d\n", n, max_len);
		printf("Case %d\n", ++nCase);
		for (i = 0; i < n; ++i) {
			gets(s);
			//puts(s);
			t[0] = tolower(s[0]);
			ls = strlen(s);
			for (j = ls - 1; j > 0; --j) {
				if (s[j] == ' ') break;
			}
			if (j > 0)	j++;
			for (k = 1; k < max_len && j < ls; ++k) {
				if (isalnum(s[j])) {
					t[k] = tolower(s[j]);
				} else {
					--k;
				}
				++j;
			}
			t[k] = 0;
			if (false == db[t]) {
				db[t] = true;
				puts(t);
			} else {
				if (k <= max_len-1) {
					p = k;
					t[k + 1] = 0;
				} else {
					p = k - 1;
				}
				for (d = 1; d <= 9; ++d) {
					t[p] = '0' + d;
					if (false == db[t]) {
						db[t] = true;
						puts(t);
						break;
					}
				}
				if (d == 10) {
					if (k <= max_len - 2) {
						p = k;
						t[k + 2] = 0;
					} else if (k == max_len - 1) {
						p = k - 1;
						t[p + 2] = 0;
					} else {
						p = k - 2;
					}
					for (d = 10; d <= 99; ++d) {
						t[p] = '0' + d / 10;
						t[p + 1] = '0' + d % 10;
						if (false == db[t]) {
							db[t] = true;
							puts(t);
							break;
						}
					}
					if (d == 100) {
						while(1) printf("add %s error\n", t);
					}
				}
			}
		}
		//n = 0, max_len = 0;
	}
	return 0;
}

