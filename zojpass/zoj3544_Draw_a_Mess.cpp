/* zoj 3544 Draw a Mess */
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXN 200
#define MAXM 50000

inline int abs(int a) { return a>=0?a:-a;}
inline int min(int a, int b) { return a<b?a:b;}
inline int max(int a, int b) { return a>b?a:b;}

struct Line {
	int f[MAXM+1], c[MAXM+1];
	void init(int m) {
		int i;
		for (i = 0; i <= m; i++) f[i] = -1, c[i] = 0;
	}
	int find(int x) {
		if (f[x] == -1 || x == f[x]) return x;
		return f[x] = find(f[x]); 
	}
};
Line line[MAXN+1];

struct Paint{
	int xc, yc, r, c, l, w;
	char type;
};
Paint pt[50000];
int color[10];

void init(int n, int m)
{
	int i, j;
	for (i = 0; i < n; ++i) line[i].init(m);
}

void draw_line(int x, int y1, int y2, int c)
{
	int i, a, b;
	for (a = y1; a <= y2; ++a) {
		if (line[x].f[a] != -1) {
			a = line[x].find(a);
			continue;
		}
		for (b = a; b <= y2; ++b) {
			if (line[x].f[b] != -1) break;
		}
		--b;
		for (i = a; i <= b; i++) line[x].f[i] = b;
		line[x].c[b] = c;
		color[c] += b - a  + 1;
		a = b;
	}
}

int main()
{
	int i, x, x_st, x_ed, y1, y2, dx, dy, tmp;
	int n, m, q, b;
	char str[256];
	while (3 == scanf("%d %d %d", &n, &m, &q)) {
		init(n, m);
		memset(color, 0, sizeof(color));
		for (i = 0; i < q; ++i) {
			scanf("%s", str);
			pt[i].type = str[0];
			if (str[0] == 'C') // Circle
				scanf("%d %d %d %d", &pt[i].xc, &pt[i].yc, &pt[i].r, &pt[i].c);
			else if (str[0] == 'D') // Diamond
				scanf("%d %d %d %d", &pt[i].xc, &pt[i].yc, &pt[i].r, &pt[i].c);
			else if (str[0] == 'R') // Rectangle
				scanf("%d %d %d %d %d", &pt[i].xc, &pt[i].yc, &pt[i].l, &pt[i].w, &pt[i].c);
			else if (str[0] == 'T') // Triangle
				scanf("%d %d %d %d", &pt[i].xc, &pt[i].yc, &pt[i].w, &pt[i].c);
		}
		for (i = q-1; i >= 0; --i) {
			if (pt[i].type == 'C') {  /// Circle
				x_st = max(pt[i].xc - pt[i].r, 0);
				x_ed = min(pt[i].xc + pt[i].r, n-1);
				for (x = x_st; x <= x_ed; ++x) {
					dx = abs(pt[i].xc - x);
					tmp = pt[i].r*pt[i].r - dx*dx;
					if (tmp < 0) continue;
					dy = (int)sqrt(tmp);
					y1 = pt[i].yc - dy;
					if (y1 < 0) y1 = 0;
					y2 = pt[i].yc + dy;
					if (y2 > m-1) y2 = m-1;
					draw_line(x, y1, y2, pt[i].c);
				}
			}
			else if (pt[i].type == 'D') { /// Diamond
				x_st = max(pt[i].xc - pt[i].r, 0);
				x_ed = min(pt[i].xc + pt[i].r, n-1);
				for (x = x_st; x <= x_ed; ++x) {
					dy = pt[i].r - abs(pt[i].xc  - x);
					y1 = pt[i].yc - dy;
					if (y1 < 0) y1 = 0;
					y2 = pt[i].yc + dy;
					if (y2 > m-1) y2 = m-1;
					draw_line(x, y1, y2, pt[i].c);
				}
			}
			else if (pt[i].type == 'R') { /// Rectangle
				x_st = pt[i].xc;
				x_ed = min(pt[i].xc + pt[i].l - 1, n-1);
				y1 = pt[i].yc;
				y2 = min(pt[i].yc + pt[i].w - 1, m-1);
				for (x = x_st; x <= x_ed; ++x) {
					draw_line(x, y1, y2, pt[i].c);
				}
			}
			else if (pt[i].type == 'T') { /// Triangle
				 /*	x_st = max(pt[i].xc - pt[i].w / 2, 0);
					x_ed = min(pt[i].xc + pt[i].w / 2, n-1);
					y1 = pt[i].yc;
					for (x = x_st; x <= x_ed; ++x) {
					if (x <= pt[i].xc) dy = x - (pt[i].xc - pt[i].w / 2);
					else dy = (pt[i].xc + pt[i].w / 2) - x;
					y2 = y1 + dy;
					if (y2 > m - 1) y2 = m - 1;
					draw_line(x, y1, y2, pt[i].c);
					} */
				x_st = pt[i].xc;
				x_ed = min(pt[i].xc + pt[i].w  / 2, n-1);
				for (x = x_st; x <= x_ed; ++x) {
					dy = (pt[i].w - (x - pt[i].xc)*2)/2;
					y1 = max(pt[i].yc - dy, 0);
					y2 = min(pt[i].yc + dy, m-1);
					draw_line(x, y1, y2, pt[i].c);
				}
			}
		}
		for (i = 1; i < 9; ++i) printf("%d ", color[i]);
		printf("%d\n", color[9]);
	}
	return 0;
}

