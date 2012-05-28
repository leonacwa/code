#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 50000 + 10;
const int MAXS = 100000 + 100;

int A[MAXN], B[MAXN];
int L[MAXN], R[MAXN];
int T[MAXS * 2 * 4];

void make_tree(int idx, int begin, int end)
{
	T[idx] = -1;
	if (begin == end) {
		return;
	}
	int mid = (end - begin) / 2 + begin;
	make_tree(idx * 2, begin, mid);
	make_tree(idx * 2 + 1, mid + 1, end);
}

void update(int idx, int begin, int end, int l, int r, int val)
{
	if (end < l || r < begin) {
		return;
	}
	if (l <= begin && end <= r) {
		T[idx] = val;
	} else {
		int mid = (end - begin) / 2 + begin;
		update(idx * 2, begin, mid, l, r, val);
		update(idx * 2 + 1, mid + 1, end, l, r, val);
	}
}

int query(int idx, int begin, int end, int x)
{
	if (begin == x && x == end) {
		return T[idx];
	}
	int mid = (end - begin) / 2 + begin;
	int val;
	if (x <= mid) {
		val = query(idx * 2, begin, mid, x);
	} else {
		val = query(idx * 2 + 1, mid + 1, end, x);
	}
	return val > T[idx] ? val : T[idx];
}

int min_path(int k, int x)
{
	if (k == -1) {
		return x < 0 ? -x : x;
	}
	return min(L[k] + x - A[k], R[k] + B[k] - x);
}

int main()
{
	int n, s;
	while (EOF != scanf("%d %d", &n, &s)) {
		make_tree(1, -MAXS, MAXS); 
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &A[i], &B[i]);
			L[i] = min_path(query(1, -MAXS, MAXS, A[i]), A[i]);
			R[i] = min_path(query(1, -MAXS, MAXS, B[i]), B[i]);
			update(1, -MAXS, MAXS, A[i], B[i], i);
		}
		printf("%d\n", min_path(n-1, s));
	}
	return 0;
}

