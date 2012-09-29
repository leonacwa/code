// A AC
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100000 + 100;
char str[MAXN];
char out[MAXN];

int main()
{
	while (EOF != scanf("%s", str)) {
		int n = strlen(str);
		int len = 1;
		out[0] = str[0];
		for (int i = 1; i < n; ++i) {
			int l = 0, r = len - 1;
			while (l < r) {
				int m = l + (r - l) / 2;
				if (out[m] >= str[i]) {
					l = m + 1;
				} else {
					r = m;
				}
			}
			if (out[l] >= str[i]) ++l;
			out[l] = str[i];
			len = l + 1;
		}
		out[len] = 0;
		puts(out);
	}
	return 0;
}

