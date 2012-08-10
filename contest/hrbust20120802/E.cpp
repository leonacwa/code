#include <iostream>
#include <cmath> 
#include <vector> 
#include <algorithm> 
#define MAX_N 100
using namespace std;

///////////////////////////////////////////////////////////////////
//常量区
const double INF        = 1e10;     // 无穷大 
const double EPS        = 1e-15;    // 计算精度 
const int LEFT          = 0;        // 点在直线左边 
const int RIGHT         = 1;        // 点在直线右边 
const int ONLINE        = 2;        // 点在直线上 
const int CROSS         = 0;        // 两直线相交 
const int COLINE        = 1;        // 两直线共线 
const int PARALLEL      = 2;        // 两直线平行 
const int NOTCOPLANAR   = 3;        // 两直线不共面 
const int INSIDE        = 1;        // 点在图形内部 
const int OUTSIDE       = 2;        // 点在图形外部 
const int BORDER        = 3;        // 点在图形边界 
const int BAOHAN        = 1;        // 大圆包含小圆
const int NEIQIE        = 2;        // 内切
const int XIANJIAO      = 3;        // 相交
const int WAIQIE        = 4;        // 外切
const int XIANLI        = 5;        // 相离
///////////////////////////////////////////////////////////////////
struct Point { // 二维点或矢量 
    double x, y; 
    double angle, dis; 
    Point() {} 
    Point(double x0, double y0): x(x0), y(y0) {} 
};
struct Line {
	double a, b, c;
};
struct Seg{
	Point s,e;
	Seg() {}
	Seg(Point a,Point b){s=a;e=b;}
};

///////////////////////////////////////////////////////////////////
//基本函数区
inline double max(double x,double y) 
{ 
    return x > y ? x : y; 
} 
inline double min(double x, double y) 
{ 
    return x > y ? y : x; 
} 
inline bool ZERO(double x)              // x == 0 
{ 
    return (fabs(x) < EPS); 
} 
inline bool ZERO(Point p)               // p == 0 
{ 
    return (ZERO(p.x) && ZERO(p.y)); 
} 
inline bool EQ(double x, double y)      // eqaul, x == y 
{ 
    return (fabs(x - y) < EPS); 
} 
inline bool NEQ(double x, double y)     // not equal, x != y 
{ 
    return (fabs(x - y) >= EPS); 
} 
inline bool LT(double x, double y)     // less than, x < y 
{ 
    return ( NEQ(x, y) && (x < y) ); 
} 
inline bool GT(double x, double y)     // greater than, x > y 
{ 
    return ( NEQ(x, y) && (x > y) ); 
} 
inline bool LEQ(double x, double y)     // less equal, x <= y 
{ 
    return ( EQ(x, y) || (x < y) ); 
} 
inline bool GEQ(double x, double y)     // greater equal, x >= y 
{ 
    return ( EQ(x, y) || (x > y) ); 
} 
// 注意！！！ 
// 如果是一个很小的负的浮点数 
// 保留有效位数输出的时候会出现-0.000这样的形式， 
// 前面多了一个负号 
// 这就会导致错误！！！！！！ 
// 因此在输出浮点数之前，一定要调用次函数进行修正！ 
inline double FIX(double x) 
{ 
    return (fabs(x) < EPS) ? 0 : x; 
} 
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//二维矢量运算 
bool operator==(Point p1, Point p2)  
{ 
    return ( EQ(p1.x, p2.x) &&  EQ(p1.y, p2.y) ); 
} 
bool operator!=(Point p1, Point p2)  
{ 
    return ( NEQ(p1.x, p2.x) ||  NEQ(p1.y, p2.y) ); 
} 
bool operator<(Point p1, Point p2) 
{ 
    if (NEQ(p1.x, p2.x)) { 
        return (p1.x < p2.x); 
    } else { 
        return (p1.y < p2.y); 
    } 
} 
Point operator+(Point p1, Point p2)  
{ 
    return Point(p1.x + p2.x, p1.y + p2.y); 
} 
Point operator-(Point p1, Point p2)  
{ 
    return Point(p1.x - p2.x, p1.y - p2.y); 
} 
double operator*(Point p1, Point p2) // 计算叉乘 p1 × p2 
{ 
    return (p1.x * p2.y - p2.x * p1.y); 
} 
double operator&(Point p1, Point p2) { // 计算点积 p1·p2 
    return (p1.x * p2.x + p1.y * p2.y); 
} 
double Norm(Point p) // 计算矢量p的模 
{ 
    return sqrt(p.x * p.x + p.y * p.y); 
} 
// 把矢量p旋转角度angle (弧度表示) 
// angle > 0表示逆时针旋转 
// angle < 0表示顺时针旋转 
Point Rotate(Point p, double angle) 
{ 
    Point result; 
    result.x = p.x * cos(angle) - p.y * sin(angle); 
    result.y = p.x * sin(angle) + p.y * cos(angle); 
    return result; 
} 
//////////////////////////////////////////////////////////////////////////////////////
double Area(Point A, Point B, Point C) //三角形面积 
{ 
    return ((B-A)*(C-A) / 2.0); 
}
/////////////////////////////////////


const double eps = 1e-8;
const double pi = acos(-1.0);
#define sgn(x) (fabs(x)<eps?0:(x>0?1:-1))

inline double Cross(Point a, Point b, Point c) {
	return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y); 
};

Line Turn(Point s, Point e) {
	Line ln;
	ln.a =s.y - e.y ;
	ln.b =e.x - s.x;
	ln.c =s.x*e.y - e.x*s.y;
	return ln;
}
bool dotOnSeg(Point p, Point s, Point e) { 
	if ( p == s || p == e ) 
		return true;
	return sgn(Cross(s,e,p))==0 && 
		sgn((p.x-s.x)*(p.x-e.x))<=0 && sgn((p.y-s.y)*(p.y-e.y))<=0;//sgn可能等于0，比如线段垂直坐标轴
}
bool Seg_Inst(Seg s1, Seg s2, Point &p) {//判断线段相交，共线时需要特判,先判直线相交，再判点在直线上 
	Line l1=Turn(s1.s,s1.e),l2=Turn(s2.s,s2.e);
	double d = l1.a*l2.b - l2.a*l1.b;
	if ( sgn(d) ==0 ) return false;
	p.x = (-l1.c*l2.b + l2.c*l1.b) / d;
	p.y = (-l1.a*l2.c + l2.a*l1.c) / d;
	return dotOnSeg(p,s1.s,s1.e) && dotOnSeg(p,s2.s,s2.e);
}

int main() {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	while (EOF != scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4)) {
		Seg s1(Point(x1, y1), Point(x2, y2)), s2(Point(x3, y3), Point(x4, y4));
		Point p;
		double ans = 0.0;
		if (Seg_Inst(s1, s2, p) || (y2 == y4)) {
			printf("inst %f %f\n", p.x, p.y);
			printf("%f %f, %f %f\n", s1.e.x, s1.e.y, s2.e.x, s2.e.y);
			ans = Area(s1.e, s2.e, p);
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
