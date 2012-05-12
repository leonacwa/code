#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

const int NN = 500;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
struct Knight {
	int id, x, y, t;
	Knight(int tid = 0, int tx = 0, int ty = 0, int tt = 0) :id(tid), x(tx), y(ty), t(tt)
	{}
	bool operator < (const Knight &b) const {
		if (t != b.t) return t < b.t;
		return id < b.id;
	}
};

struct Node {
	int x, y, t;
	Node(int tx = 0, int ty = 0, int tt = 0) : x(tx), y(ty), t(tt)
	{}
};

Knight A[NN], B[NN];
char mm[NN][NN];
int mm_t[NN][NN];
int n, m, w, h;

void init_bfs_t()
{
	queue<Node> Q;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			mm_t[i][j] = INT_MAX;
		}
	}
	mm_t[0][0] = 0;
	mm_t[0][w-1] = 0;
	mm_t[h-1][0] = 0;
	mm_t[h-1][w-1] = 0;
	Q.push(Node(0, 0, 0));
	Q.push(Node(0, w-1, 0));
	Q.push(Node(h-1, 0, 0));
	Q.push(Node(h-1, w-1, 0));

	while (!Q.empty()) {
		Node tk = Q.front();
		Q.pop();
		for (int i = 0; i < 4; ++i) {
			Node tk2 = tk;
			tk2.x += dx[i];
			tk2.y += dy[i];
			tk2.t++;
			if (0 <= tk2.x && tk2.x < h && 0 <= tk2.y && tk2.y < w && mm[tk2.x][tk2.y] == '.' && tk2.t < mm_t[tk2.x][tk2.y]) {
				mm_t[tk2.x][tk2.y] = tk2.t;
				Q.push(tk2);
			}
		}
	}
}

int next[NN];
void get_next(Knight a[], int n)
{
	next[0] = -1;
	int k = -1;
	for (int i = 1; i < n; ++i) {
		while (k >= 0 && a[i].t != a[k+1].t) {
			k = next[k];
		}
		if (a[i].t == a[k+1].t) ++k;
		next[i] = k;
	}
}

int kmp(Knight A[], int nA, Knight B[], int nB)
{
	get_next(B, nB);
	int j = -1, ret = 0;
	for (int i = 0; i < nA; ++i) {
		while (j >= 0 && A[i].t != B[j+1].t) {
			j = next[j];
		}
		if (A[i].t == B[j+1].t) ++j;
		if (j + 1 > ret) ret = j + 1;
		if (j + 1 == nB) break;
	}
	return ret;
}

int main()
{
	while (EOF != scanf("%d %d %d %d", &n, &m, &w, &h)) {
		for (int i = 0; i < h; ++i) {
			scanf("%s", mm[i]);
		}
		init_bfs_t();
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &A[i].x, &A[i].y);
			A[i].id = i;
			A[i].t = mm_t[A[i].x][A[i].y];
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d %d", &B[i].x, &B[i].y);
			B[i].id = i;
			B[i].t = mm_t[B[i].x][B[i].y];
		}
		sort(A, A+n);
		sort(B, B+m);
		for (int i = 0; i < n; ++i) {
			A[i].id = i;
			if (A[i].t == INT_MAX) {
				n = i;
				break;
			}
		}
		for (int i = 0; i < m; ++i) {
			B[i].id = i;
			if (B[i].t == INT_MAX) {
				m = i;
				break;
			}
		}
		int ans = 0;
		if (n > m) {
			for (int i = 0; i < m; ++i) {
				int ret = kmp(A, n, B+i, m-i);
				if (ret > ans) ans = ret;
				if (ans > m-i) break;
			}
		} else {
			for (int i = 0; i < n; ++i) {
				int ret = kmp(B, m, A+i, n-i);
				if (ret > ans) ans = ret;
				if (ans > n-i) break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

