/* HDU 4277 USACO ORZ
 * 暴搜+map判重，卡时间过的
 * */
#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
using namespace std;
typedef pair<int, int> PII;

int n;
int l[16];
map<PII , bool> ma;
int ans;

inline bool is_tri(int a, int b, int c) {
	return a+b > c && a+c > b && c+b > a;
}

void cal(int x, int la, int lb, int lc) {
	if (lc == 0) return;
	PII p;
	if (la && lb && lc && la <= lb && lb <= lc && is_tri(la, lb, lc)) {
		p = make_pair(la, lb);
		if(!ma[p])	{
		   	++ans;
			ma[p] = true;
		}
	}
	if (x == n) return;
	cal(x+1, la + l[x], lb, lc - l[x]);  
	cal(x+1, la, lb + l[x], lc - l[x]);
	cal(x+1, la, lb, lc);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int len = 0;
		for (int i = 0; i < n; ++i) 
		{
			scanf("%d", &l[i]);
			len += l[i];
		}
		ans = 0;
		ma.clear();
		cal(0, 0, 0, len);
		printf("%d\n", ans);
	}
	return 0;
}
