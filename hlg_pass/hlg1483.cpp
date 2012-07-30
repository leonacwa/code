#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

char s[1024];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int N = 2, S = 5, E = 3, W = 4, top = 1, bottom = 6, x = 0, y = 0, d = 1, t, cnt = 1;
		scanf("%s", s);
		for (char *c = s; *c && *c != '.'; ++c) {
			if (*c == 'X') {
				if (d == 1) {
					++x;
					t = top;
					top = E;
					E = bottom;
					bottom = W;
					W = t;
				} else {
					--x;

					t = top;
					top = W;
					W = bottom;
					bottom = E;
					E = t;

				}
			} else if (*c == 'Y') {
				if (d == 1) {
					++y;
					t = top;
					top = N;
					N = bottom;
					bottom = S;
					S = t;

				} else {
					--y;

					t = top;
					top = S;
					S = bottom;
					bottom = N;
					N = t;

				}
			} else if (*c == '+') {
				d = 1;
			} else if (*c == '-') {
				d = 0;
			} else if (isdigit(*c)) {
				cnt = 0;
				for (; isdigit(*c); ++c) {
					cnt = cnt * 10 + *c - '0';
				}
				int r = cnt % 4;
				if (*c == 'X') {
					if (d == 1) {
						x += cnt - r;
					} else {
						x -= cnt - r;
					}
				} else if (*c == 'Y') {
					if (d == 1) {
						y += cnt - r;
					} else {
						y -= cnt - r;
					}
				} 
				cnt = r;
				++cnt;
			} else {
				for(;;);
				puts("error");
			}
			--cnt;
			if (cnt > 0) {
				--c;
			} else cnt = 1;
		}
		printf("position (%d,%d), %d dots\n", x, y, top);
	}
	return 0;
}
