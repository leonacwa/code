#include <cstdio>
#include <cstring>
#include <cmath>

struct Point {
	double x, y;
	Point() {}
	Point(double tx, double ty) : x(tx), y(ty) {}
};
/* 判断线段与直线是否相交
 * 语法：result=lineintersect(Point p1,Point p2,Point p3,Point p4);
 * 参数：
 * p1、p2：线段的两个端点
 * p3、p4：直线上的两个点
 * 返回值：0：线段直线不相交；1：线段和直线相交
 * 注意： 如线段在直线上，返回 1
 * */
int lineintersect(Point p1, Point p2, Point p3, Point p4) {
	Point tp1, tp2, tp3;
	tp1.x = p1.x - p3.x;
	tp1.y = p1.y - p3.y;
	tp2.x = p4.x - p3.x;
	tp2.y = p4.y - p3.y;
	tp3.x = p2.x - p3.x;
	tp3.y = p2.y - p3.y;
	if ((tp1.x * tp2.y - tp1.y * tp2.x) * (tp2.x * tp3.y - tp2.y * tp3.x) >= 0) return 1; 
	else return 0;
}

Point pt[205], cj, cj2;

int main() {
	int n, x, y, a;
	while (EOF != scanf("%d", &n)) {
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &x, &y);
			pt[i].x = x, pt[i].y = y;
		}
		scanf("%d%d%d", &x, &y, &a);
		cj.x = x, cj.y = y;
		double a0 = 3.1415926 * a / 180;
		cj2.x = 500;
		cj2.y = (cj2.x - cj.x) * tan(a0) + cj.y;
		bool ans = false;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				ans = lineintersect(pt[i], pt[j], cj, cj2);
				if (ans) break;
			}
			if (ans) break;
		}
		puts(ans ? "Tourino Failed" : "Tourino Disappeared");
	}
	return 0;
}

