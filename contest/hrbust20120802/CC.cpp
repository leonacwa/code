#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-8;
const double pi = acos(-1.0);
#define sgn(x) (fabs(x)<eps?0:(x>0?1:-1))

struct Point {
	double x, y;
	Point(double a=0,double b=0){x=a;y=b;}
	Point operator - (const Point& t) const {
		Point tmp;
		tmp.x = x - t.x;
		tmp.y = y - t.y;
		return tmp;
	}
	bool operator < (const Point &p) const {
		return sgn(x-p.x)<0 || sgn(x-p.x)==0 && sgn(y-p.y)<0; 
	}
	bool operator == (const Point& t) const {
		return sgn(x-t.x)==0 && sgn(y-t.y)==0;
	}
} GP;

struct Line {
	double a, b, c;
};

struct Seg{
	Point s,e;
	Seg() {}
	Seg(Point a,Point b){s=a;e=b;}
};

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

bool Intersect(Point p1, Point p2, Point p3, Point p4, Point& p) {    // 直线相交
	double a1, b1, c1, a2, b2, c2, d;
	a1 = p1.y - p2.y; b1 = p2.x - p1.x; c1 = p1.x*p2.y - p2.x*p1.y;
	a2 = p3.y - p4.y; b2 = p4.x - p3.x; c2 = p3.x*p4.y - p4.x*p3.y;
	d = a1*b2 - a2*b1;
	if (!sgn(d)) return false;
	p.x = (-c1*b2 + c2*b1) / d;
	p.y = (-a1*c2 + a2*c1) / d;
	return true;
}

bool Line_Inst(Line l1, Line l2, Point &p) {// 直线相交 
	double d = l1.a*l2.b - l2.a*l1.b;
	if (!sgn(d))  return false;
	p.x = (-l1.c*l2.b + l2.c*l1.b) / d;
	p.y = (-l1.a*l2.c + l2.a*l1.c) / d;
	return true; 
}

bool Seg_Inst(Seg s1, Seg s2, Point &p) {//判断线段相交，共线时需要特判,先判直线相交，再判点在直线上 
	Line l1=Turn(s1.s,s1.e),l2=Turn(s2.s,s2.e); 
	double d = l1.a*l2.b - l2.a*l1.b;
	if ( sgn(d) ==0 ) return false;
	p.x = (-l1.c*l2.b + l2.c*l1.b) / d;
	p.y = (-l1.a*l2.c + l2.a*l1.c) / d;
	return dotOnSeg(p,s1.s,s1.e) && dotOnSeg(p,s2.s,s2.e);
}

bool check(Seg s1, Seg s2, Point& pp) {//共线，特判
	if ( s1.s==s2.s || s1.s==s2.e ) { pp = s1.s;    return true;}
	if ( s1.e==s2.s || s1.e==s2.e) {pp = s1.e;return true;}    
	return false;
}

const int MAXN = 1005;
Seg seg[MAXN];

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
			seg[i].s.x = x, seg[i].s.y = y;
			scanf("%d%d", &x, &y);
			seg[i].e.x = x, seg[i].e.y = y;
		}
		Point p;
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				if (Seg_Inst(seg[i], seg[j], p) || check(seg[i], seg[j], p)) join(i, j);
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

