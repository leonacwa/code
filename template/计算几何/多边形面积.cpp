/* 求多边形的面积
 * 传入：顶点个数n,  顶点数组 p
 * 返回：顶点个数
 * */
double AreaOfPolygon(int n, Point p[]) {
	int i;
	double area = 0;
	for (i = 0; i < n; ++i) {
		//area += p[i].x * p[(i+1)%n].y - p[i].y * p[(i+1) % n].x;
		// 如果将式子展开，可以简化成这个样子，减小运算量
		area += p[(i+1) % n].y * (p[i].x - p[(i+2) % n].x); 
	}
	return abs(area) / 2.0;
}


