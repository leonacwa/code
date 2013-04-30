
struct Point {
	double x, y;
	Point() {}
	Point(double a, double b) {
		x = a, y = b;
	}
	Point operator - (const Point &B) const {
		return Point(x - B.x, y - B.y);
	}
};

bool cmpxy(const Point &A, const Point &B) {
	return A.x < B.x || (A.x == B.x && A.y < B.y);
}

double cross(const Point &A, const Point &B) {
	return A.x * B.y - A.y * B.x;
}

int convex_hull(int n, Point pt[], Point ch[]) {
	sort(pt, pt + n, cmpxy);
	int m = 0;
	for (int i = 0; i < n; ++i) {
		while (m > 1 && cross(ch[m-1] - ch[m-2], pt[i] - ch[m-2]) <= 0) m--;
		ch[m++] = pt[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; --i) {
		while (m > k && cross(ch[m-1] - ch[m-2], pt[i] - ch[m-2]) <= 0) m--;
		ch[m++] = pt[i];
	}
	if (n > 1) m--;
	return m;
}