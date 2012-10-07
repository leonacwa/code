struct Point {
	int x, y;
};

int cross(Point p, Point q, Point p0) {
	return (p.x - p0.x) * (q.y - p0.y) - (q.x - p0.x) * (p.y - p0.y);
}
/* 点是否在线段上
 * */

int isPointOnLine(Point p, Point p1, Point p2) {
	if (cross(p, p2, p1) != 0) return false;
	return (min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x) && min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y));
}

