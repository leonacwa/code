#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50000 + 5;
int rock[MAXN];
int L, N, M;

bool check(int mid)
{
	int k = 0, j = 0;
	for (int i = 1; i < N+1; i++) {
		if (rock[i] - rock[j] < mid) {
			k++;
		} else {
			j = i;
		}
	}
	if (rock[N+1] - rock[j] < mid || k > M) return false;
	return true;
}

int main()
{
	while (EOF != scanf("%d %d %d", &L, &N, &M)) {
		for (int i = 1; i <= N; i++) {
			scanf("%d", &rock[i]);
		}
		rock[0] = 0;
		rock[N+1] = L;
		sort(rock, rock+N+2);
		int l = 0, r = L, m;
		while (l < r-1) {
			m = (r - l) / 2 + l;
			if (check(m)) {
				l = m;
			} else {
				r = m - 1;
			}
		}
		if (check(r)) {
			m = r;
		} else {
		   	m = l;
		}
		printf("%d\n", m);
	}
	return 0;
}

