/*
 * 最远(近)曼哈顿距离
 * n个二维平面点，m个查询，查询一个点的最远点。

 设距离最远的两点为i,j，可知所求的最大距离必定有以下四种形式之一：
 (xi-xj)+(yi-yj), (xj-xi)+(yi-yj), (xi-xj)+(yj-yi), (xj-xi)+(yj-yi) 变形一下，把相同点的坐标放到一起，
 即 (xi+yi)-(xj+yj), (-xi+yi)-(-xj+yj), (xi-yi)-(xj-yj), (-xi-yi)-(-xj-yj) 再变一下，把中间变成‘+'，
 即 (xi+yi)+(-xj-yj), (-xi+yi)+(xj-yj), (xi-yi)+(-xj+yj),(-xi-yi)+(xj+yj)
 由此，可以发现一个规律，即去绝对值之后把同一点的坐标放在一起，对应坐标的符号总是相反的，如(-xi+yi)与(xj-yj)。
 假如我们用0表示负号，1表示正号，则(-xi+yi)与(xj-yj)两个括号内的符号可以表示为：01和10       
 当你多举几个例子之后，就会发现，对于一个确定的维数D,符号转化成的二进制数，它们的和总是一个定值，即2^d-1，这就说明了，当我们知道了前一个点去绝对值之后的符号，就可以知道第二个点去绝对值后的符号是怎样的。
 只要对所有的点(xi,yi)，依次计算出(xi+yi),(xi-yi),(-xi+yi),(-xi-yi)这四种形式，然后把每个点i算出来的这四种情况的最大值分别记录到一个集合中，然后枚举每一种去绝对值的组合，共四种，对于每种组合从四个集合中找最大值，取四种情况的最大(小)值即可。
 代码中s_find使用set优化，可以在(lgN/lg2)时间复杂度在找到最大值或者最小值。brute_find为暴力枚举，用于验证程序。
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = int(1e6+5);

struct Point {
	int x, y;
};
int n, m;
Point pt[MAXN];
set<int> ss[4];

int s_find(int x, int y) {
	int ans = 0;
	for (int j = 0; j < 4; ++j) {
		int t = (j&2?1:-1)*x +(j&1?1:-1)*y + *ss[j].rbegin();
		ans = max(ans, t);
	}
	return ans;
}

int brute_find(int x, int y) {
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans = max(ans, abs(x - pt[i].x) + abs(y - pt[i].y));
	}
	return ans;
}

int main() {
	bool test = true;
	if (test) {
		srand(time(0));
		n = 100, m = 100;
	} else {
		scanf("%d%d", &n, &m);
	}

	for (int j = 0; j < 4; ++j) ss[j].clear();
	for (int i = 0 ; i < n; ++i) {
		if (test) {
			pt[i].x = rand() % 10000, pt[i].y = rand() % 10000;
		} else {
			scanf("%d%d", &pt[i].x, &pt[i].y);
		}
		ss[0].insert( pt[i].x + pt[i].y);
		ss[1].insert( pt[i].x - pt[i].y);
		ss[2].insert(-pt[i].x + pt[i].y);
		ss[3].insert(-pt[i].x - pt[i].y);
	}
	for (int i = 0; i < m; ++i) {
		int x, y, p;
		if (test) {
			p = rand() % m;
		} else {
			scanf("%d", &p);
		}
		x = pt[p].x, y= pt[p].y;
		int ans = s_find(x, y), ans2 = brute_find(x, y);
		if (ans != ans2) printf("error  ");
		printf("%d %d\n", ans, ans2);
	}
	return 0;
}
