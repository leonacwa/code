// 计算底面的向量n1、截面的向量n2， 底面面积S, 截面面积：A = S * ( (|n1| * |n2|) / (n1 x n2));
#include <stdio.h>
#include <string.h>
#include <math.h>

struct Point2 {
	Point2(){}
	Point2(double tx, double ty):x(tx), y(ty) {}
	int x, y;
};

struct Point3 {
	Point3(){}
	Point3(double tx, double ty, double tz):x(tx), y(ty), z(tz) {}
	double x, y, z;
};
struct Vector3 {
	Vector3(){}
	Vector3(double tdx, double tdy, double tdz) : dx(tdx), dy(tdy), dz(tdz) {}
	double dx, dy, dz;
};

Point2 btm[3];
Point3 cut[3];

double getVectorModule2(Vector3 tv) 
{
	return tv.dx*tv.dx + tv.dy*tv.dy + tv.dz*tv.dz;
}

// return (p2-p1) X (p3-p1)
double getCrossProduct(Point2 p1, Point2 p2, Point2 p3) {
	return (p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y);
}

double getDotProduct(Vector3 v1, Vector3 v2) {
	return v1.dx*v2.dx + v1.dy*v2.dy + v1.dz*v2.dz;
}

double getTriangleArea(Point2 p1, Point2 p2, Point2 p3) {
	return getCrossProduct(p1, p2, p3) / 2;
}

double getPolygonArea(Point2 pa[], int n) {
	double area = 0;
	for (int i = 1; i < n-1; i++) {
		area += getTriangleArea(pa[0], pa[i], pa[i+1]);
	}
	return fabs(area);
}

Vector3 getNormalVector(Point3 p1, Point3 p2, Point3 p3) {
	double x1 = p2.x - p1.x;
	double y1 = p2.y - p1.y;
	double z1 = p2.z - p1.z;
	double x2 = p3.x - p2.x;
	double y2 = p3.y - p2.y;
	double z2 = p3.z - p2.z;
	double d = y1*z2 - y2*z1; 
	double dx = 1;
	double dy = (-x1*z2 + x2*z1) / d;
	double dz = (-y1*x2 + y2*x1) / d;
	return Vector3(dx, dy, dz);
}

int main()
{
	int caseN;
	double x, y, z;
	scanf("%d", &caseN);
	while (caseN--) {
		for (int i = 0; i < 4; i++) {
			scanf("%lf %lf %lf",&x, &y, &z); 
			btm[i].x = y;
			btm[i].y = z;
		}
		for (int i = 0; i < 3; i++) {
			scanf("%lf %lf %lf", &cut[i].x, &cut[i].y, &cut[i].z);
		}
		double S = getPolygonArea(btm, 4);
		Vector3 n1 = Vector3(1, 0, 0);
		Vector3 n2 = getNormalVector(cut[0], cut[1], cut[2]);
		double dtp = getDotProduct(n1, n2);
		double A = sqrt((S * S * getVectorModule2(n1) * getVectorModule2(n2)) / (dtp*dtp));
		printf("%.1lf\n", A);
	}
	return 0;
}

