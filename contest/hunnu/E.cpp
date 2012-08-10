#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <queue>
using namespace std;

const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
struct Point {
	int x, y;
	Point(int tx = 0, int ty = 0) :x(tx), y(ty)
	{}
};

char s_ma[16][32];

int count(int x, int y)
{
	int ret = s_ma[x][y] == '*';
	for (int i = 0; i < 8; ++i) {
		int tx = x + dx[i], ty = y + dy[i];
		if (0 <= tx && tx < 16 && 0 <= ty && ty < 30 && s_ma[tx][ty] == '*') {
			++ret;
		}
	}
	return ret;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		int x, y;
		scanf("%d %d", &x, &y);
		for (int i = 0; i < 16; ++i) {
			scanf("%s", s_ma[i]);
		}
		x--, y--;
		queue<Point> Q;
		Q.push(Point(x, y));
		s_ma[x][y] = '0' + count(x, y);
		while (!Q.empty()) {
			Point pt = Q.front();
			Q.pop();
			x = pt.x, y = pt.y;
			if (s_ma[x][y] == '0') {
				for (int i = 0; i < 8; ++i) {
					x = pt.x + dx[i], y = pt.y + dy[i];
					if (0 <= x && x < 16 && 0 <= y && y < 30 && !isdigit(s_ma[x][y])) {
						s_ma[x][y] = '0' + count(x, y);
						if (s_ma[x][y] == '0') {
							Q.push(Point(x, y));
						}
					}
				}
			}
		}
		for (int i = 0; i < 16; ++i) {
			for (int j = 0; j < 30; ++j) {
				if (isdigit(s_ma[i][j])) {
					putchar(s_ma[i][j]);
				} else {
					putchar('#');
				}
			}
			putchar('\n');
		}
		if (nTest) puts("");
	}
	return 0;
}

