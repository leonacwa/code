#include <iostream>
#include <cmath> 
#include <vector> 
#include <algorithm> 
#define MAX_N 100
using namespace std;
const int MAXN = 1005;

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

///////////////////////////////////////////////////////////////////
//类型定义区
struct Point {              // 二维点或矢量 
	double x, y; 
	double angle, dis; 
	Point() {} 
	Point(double x0, double y0): x(x0), y(y0) {} 
}; 
struct Line {               // 二维的直线或线段 
	Point p1, p2; 
	Line() {} 
	Line(Point p10, Point p20): p1(p10), p2(p20) {} 
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

bool LineSegIntersect(Line L1, Line L2) // 判断二维的两条线段是否相交 
{ 
	return ( GEQ( max(L1.p1.x, L1.p2.x), min(L2.p1.x, L2.p2.x) ) && 
			GEQ( max(L2.p1.x, L2.p2.x), min(L1.p1.x, L1.p2.x) ) && 
			GEQ( max(L1.p1.y, L1.p2.y), min(L2.p1.y, L2.p2.y) ) && 
			GEQ( max(L2.p1.y, L2.p2.y), min(L1.p1.y, L1.p2.y) ) && 
			LEQ( ((L2.p1 - L1.p1) * (L1.p2 - L1.p1)) * ((L2.p2 -  L1.p1) * (L1.p2 - L1.p1)), 0 ) && 
			LEQ( ((L1.p1 - L2.p1) * (L2.p2 - L2.p1)) * ((L1.p2 -  L2.p1) * (L2.p2 - L2.p1)), 0 ) );              
} 
Line seg[MAXN];

int fa[MAXN];
int find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		fa[fy] = fx;
	}
}

int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		for (int i = 1, x, y; i <= n; ++i) {
			fa[i] = i;
			scanf("%d%d", &x, &y);
			seg[i].p1.x = x, seg[i].p1.y = y;
			scanf("%d%d", &x, &y);
			seg[i].p2.x = x, seg[i].p2.y = y;
		}
		Point p;
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				if (LineSegIntersect(seg[i], seg[j])) join(i, j);
			}
		}
		int a, b;
		while (EOF != scanf("%d%d", &a, &b)) {
			if (a == 0 && b == 0) break;
			if (find(a) == find(b)) {
				puts("CONNECTED");
			} else {
				puts("NOT CONNECTED");
			}
		}
	}
	return 0;
}

