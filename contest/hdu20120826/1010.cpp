#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAXN=505;
const double EPS=1e-8;

struct Point
{
	double x,y,z;
	Point(){}
	Point(double xx,double yy,double zz):x(xx),y(yy),z(zz){}

	Point operator -(const Point p1)                                           //两向量之差 
	{
		return Point(x-p1.x,y-p1.y,z-p1.z);
	}

	Point operator *(Point p)                                                 //叉乘 
	{
		return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	} 

	double operator ^(Point p)                                               //点乘 
	{
		return (x*p.x+y*p.y+z*p.z);
	}
};

struct CH3D
{
	struct face
	{
		int a,b,c;                                                        //表示凸包一个面上三个点的编号
		bool ok;                                                          //表示该面是否属于最终凸包中的面
	};

	int n;                                                                   //初始顶点数 
	Point P[MAXN];                                                           //初始顶点

	int num;                                                                 //凸包表面的三角形数
	face F[8*MAXN];  

	int g[MAXN][MAXN];                                                       //凸包表面的三角形

	double vlen(Point a)                                                     //向量长度
	{
		return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
	}

	Point cross(const Point &a, const Point &b, const Point &c)             //叉乘 
	{
		return Point((b.y-a.y)*(c.z-a.z)-(b.z-a.z)*(c.y-a.y),-((b.x-a.x)*(c.z-a.z)-(b.z-a.z)*(c.x-a.x)),(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x));
	}

	double area(Point a,Point b,Point c)                                   //三角形面积*2
	{
		return vlen((b-a)*(c-a));
	}

	double volume(Point a,Point b,Point c,Point d)                        //四面体有向体积*6
	{
		return (b-a)*(c-a)^(d-a);
	}

	double dblcmp(Point &p,face &f)                                       //正:点在面同向
	{
		Point m=P[f.b]-P[f.a];
		Point n=P[f.c]-P[f.a];
		Point t=p-P[f.a];
		return (m*n)^t;
	}

	void deal(int p,int a,int b)
	{
		int f=g[a][b];
		face add;
		if(F[f].ok)
		{
			if(dblcmp(P[p],F[f])>EPS)
				dfs(p,f);
			else
			{
				add.a=b;    
				add.b=a;
				add.c=p;
				add.ok=1;
				g[p][b]=g[a][p]=g[b][a]=num;
				F[num++]=add;
			}
		}
	}

	void dfs(int p,int now)
	{
		F[now].ok=0;
		deal(p,F[now].b,F[now].a);
		deal(p,F[now].c,F[now].b);
		deal(p,F[now].a,F[now].c);
	}

	bool same(int s,int t)
	{
		Point &a=P[F[s].a];
		Point &b=P[F[s].b];
		Point &c=P[F[s].c];
		return fabs(volume(a,b,c,P[F[t].a]))<EPS && fabs(volume(a,b,c,P[F[t].b]))<EPS
			&& fabs(volume(a,b,c,P[F[t].c]))<EPS;
	}

	void solve()                                                         //构建三维凸包
	{
		int i,j,tmp;
		face add;
		bool flag=true;
		num=0;
		if(n<4)
			return;
		for(i=1;i<n;i++)                                              //此段是为了保证前四个点不共面,若以保证,则可去掉
		{
			if(vlen(P[0]-P[i])>EPS)
			{
				swap(P[1],P[i]);
				flag=false;
				break;
			}
		}
		if(flag)
			return;
		flag=true;
		for(i=2;i<n;i++)                                             //使前三点不共线
		{
			if(vlen((P[0]-P[1])*(P[1]-P[i]))>EPS)
			{
				swap(P[2],P[i]);
				flag=false;
				break;
			}
		}
		if(flag)
			return;
		flag=true;
		for(i=3;i<n;i++)                                            //使前四点不共面
		{
			if(fabs((P[0]-P[1])*(P[1]-P[2])^(P[0]-P[i]))>EPS)
			{
				swap(P[3],P[i]);
				flag=false;
				break;
			}
		}
		if(flag)
			return;
		for(i=0;i<4;i++)
		{
			add.a=(i+1)%4;
			add.b=(i+2)%4;
			add.c=(i+3)%4;
			add.ok=true;
			if(dblcmp(P[i],add)>0)
				swap(add.b,add.c);
			g[add.a][add.b]=g[add.b][add.c]=g[add.c][add.a]=num;
			F[num++]=add;
		}
		for(i=4;i<n;i++)
		{
			for(j=0;j<num;j++)
			{
				if(F[j].ok && dblcmp(P[i],F[j])>EPS)
				{
					dfs(i,j);
					break;
				}
			}
		}
		tmp=num;
		for(i=num=0;i<tmp;i++)
			if(F[i].ok)
			{
				F[num++]=F[i];
			}
	}

	double area()                                                     //表面积
	{
		double res=0.0;
		if(n==3)
		{
			Point p=cross(P[0],P[1],P[2]);
			res=vlen(p)/2.0;
			return res;
		}        
		for(int i=0;i<num;i++)
			res+=area(P[F[i].a],P[F[i].b],P[F[i].c]);
		return res/2.0;
	}

	double volume()                                                  //体积
	{
		double res=0.0;
		Point tmp(0,0,0);
		for(int i=0;i<num;i++)
			res+=volume(tmp,P[F[i].a],P[F[i].b],P[F[i].c]);
		return fabs(res/6.0);
	}

	int triangle()                                                  //表面三角形个数    
	{
		return num;
	}

	int polygon()                                                   //表面多边形个数
	{
		int i,j,res,flag;
		for(i=res=0;i<num;i++)
		{
			flag=1;
			for(j=0;j<i;j++)
				if(same(i,j))
				{
					flag=0;
					break;
				}
			res+=flag;
		}
		return res;
	}
};

CH3D hull;

int main()
{
	int i;
	double res;
	while(scanf("%d",&hull.n)!=EOF)
	{
		for(i=0;i<hull.n;i++)
			scanf("%lf%lf%lf", &hull.P[i].x, &hull.P[i].y, &hull.P[i].z);
		hull.solve();
		res=hull.area();
		printf("%.3lf\n",res);
	}
	return 0;
} 
