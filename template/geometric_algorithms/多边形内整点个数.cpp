/* 
 * [Pick定理]    设以整数点为顶点的多边形的面积为S， 多边形内部的整数点数为N, 多边形边界上的整数点数为L， 则 
 * N + L/2 - 1 = S
 * */

struct Point {
	int x, y;
};
int abs(int a) {
	return a < 0 ? -a : a;
}

int gcd(int a, int b) {
	int t;
	while (b) {
		t = a % b; a = b; b = t;
	}
	return a;
}
/* 多边形边上的整点个数
 * */
int getIntPointOnEdge(int n, Point p[]) {
	int i, ret = 0;
	for (i = 0; i < n; ++i) {
		ret += gcd(abs(p[i].x - p[(i+1)%n].x), abs(p[i].y - p[(i+1) % n].y));
	}
	return ret;
}
/* 多边形内整点个数
 * */
int getIntPointInPolygon(int n, Point p[]) {
	int i, area = 0;
	for (i = 0; i < n; ++i) {
		//area += p[i].x * p[(i+1)%n].y - p[i].y * p[(i+1) % n].x;
		// 如果将式子展开，可以简化成这个样子，减小运算量
		area += p[(i+1) % n].y * (p[i].x - p[(i+2) % n].x);
	}
	return (abs(area) - getIntPointOnEdge(n, p)) / 2 + 1;
}

