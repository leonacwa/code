/*
 * HDU 4433 locker
 * Asia 2012 ACM-ICPC Tianjin Onsite C.locker
 * BFS solution
 * */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;

const int INF = 99999999;
const int MAXN = 1005;
int n;
char sa[MAXN], sb[MAXN];
int f[MAXN][100];
bool inq[MAXN][100];
queue< pair<int,int> > que;

void check(int l, int s, int l2, int s2, int v) {
	if (f[l2][s2] > f[l][s] + v) {
		f[l2][s2] = f[l][s] + v;
		if (!inq[l2][s2]) {
			que.push( make_pair(l2, s2) );
			inq[l2][s2] = 1;
		}
	}
}

int spfa() {
	for (int i = 0; i < n + 2; ++i) {
		for (int j = 0; j < 100; ++j) {
			f[i][j] = INF;
			inq[i][j] = 0;
		}
	}
	int s = sa[0] * 10 + sa[1];
	f[0][s] = 0;
	inq[0][s] = 1;
	que.push(make_pair(0, s));
	while (!que.empty()) {
		int l = que.front().first;
		int s = que.front().second;
		que.pop();
		inq[l][s] = 0;
		int a = s / 10, b = s % 10;
		int t = (sb[l] - a + 10) % 10;
		for (int i = 0; i <= t; ++i) {
			for (int j = 0; j <= i; ++j) {
				int s2 = (b + i) % 10 * 10 + (sa[l+2]+j) % 10;
				check(l, s, l+1, s2, t);
			}
		}
	   	t = 10 - t;
		for (int i = 0; i <= t; ++i) {
			for (int j = 0; j <= i; ++j) {
				int s2 = (b - i + 10) % 10 * 10 + (sa[l+2]-j+10) % 10;
				check(l, s, l+1, s2, t);
			}
		}
	}
	return f[n][0];
}

int main() {
	while (EOF != scanf("%s%s", sa, sb)) {
		n = strlen(sa);
		for (int i = 0; i < n; ++i) {
			sa[i] -= '0';
			sb[i] -= '0';
		}
		sa[n] = sa[n+1] = sa[n+2] = 0;
		sb[n] = sb[n+1] = sb[n+2] = 0;
		printf("%d\n", spfa());
	}
	return 0;
}
