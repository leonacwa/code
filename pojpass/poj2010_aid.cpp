#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 100;
struct Node {
	int s, f;
	bool operator < (const Node &B) const {
		return s < B.s;
	}
} node[MAXN];

int before[MAXN];
int heap[MAXN];
int heap_size, heap_sum;

void adjust(int c)
{
	int *p = heap - 1;
	int val = p[c];
	while (c * 2 <= heap_size) {
		int lc = c * 2;
		if (lc < heap_size && p[lc+1] > p[lc]) {
			++lc;
		}
		if (p[lc] > val) {
			p[c] = p[lc];
			c = lc;
		} else {
			break;
		}
	}
	p[c] = val;
}

void init_heap(int l, int r)
{
	heap_sum = 0;
	for (int i = l; i <= r; ++i) {
		heap[i - l] = node[i].f;
		heap_sum += node[i].f;
	}
	for (int i = heap_size / 2; i > 0; --i) {
		adjust(i);
	}
}

void update_heap(int f)
{
	int *p = heap - 1;
	if (f < p[1]) {
		heap_sum -= p[1] - f;
		p[1] = f;
		adjust(1);
	}
}

int main()
{
	int n, c, f;
	while (EOF != scanf("%d %d %d", &n, &c, &f)) {
		for (int i = 0; i < c; ++i) {
			scanf("%d %d", &node[i].s, &node[i].f);
		}
		sort(node, node + c);
		heap_size = n / 2;
		init_heap(0, heap_size - 1);
		for (int i = heap_size; i < c - heap_size; ++i) {
			before[i] = heap_sum;
			update_heap(node[i].f);
		}
		int ans = -1;
		init_heap(c - heap_size, c - 1);
		for (int i = c - heap_size - 1; i >= heap_size; --i) {
			int t = before[i] + heap_sum + node[i].f;
			if (0 <= t && t <= f) {
				ans = node[i].s;
				break;
			}
			update_heap(node[i].f);
		}
		printf("%d\n", ans);
	}
	return 0;
}

