struct Point {
	double x, y;
	Point() {}
	Point(double tx, double ty) : x(tx), y(ty) {}
};
/* 两条线段p, q相交
 * 传入：p1, p2 线段1的两个端点，  q1,q2线段2的两个端点 
 * 返回：true 线段相交
 * */
bool isSegInter(Point p1, Point p2, Point q1, Point q2) {
	return (
			min(p1.x, p2.x) <= max(q1.x, q2.x) &&
			min(q1.x, q2.x) <= max(p1.x, p2.x) &&
			min(p1.y, p2.y) <= max(q1.y, q2.y) &&
			min(q1.y, q2.y) <= max(p1.y, p2.y) && /* 跨立实验 */
			cross(p1, q2, q1) * cross(p2, q2, q1) <= 0 && 
			cross(q1, p2, p1) * cross(q2, p2, p1) <= 0  /* 叉积相乘判方向 */
		   );
}
