#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 55;
const int MM = 505;

struct Edge {
	int u, v, w;
	int cnt, t[32];
} E[MM];
int n, m;
int len[NN];

int minTime(int now, int w, int c, int t[])
{
	if (c == 0) {
		return now + w;
	}
	for (int i = 0; i < c; i += 2) {
		if (w <= t[i] - now) {
			return now + w;
		}
		if (now < t[i+1]) {
			now = t[i+1];
		}
	}
	if (c % 2 == 0) {
		return max(now, t[c - 1]) + w;
	}
	return INT_MAX;
}

int bellman_ford(int begin, int end)
{
	for (int i = 0; i <= n; ++i) {
		len[i] = INT_MAX;
	}
	len[begin] = 0;
	for (int i = 0; i < n; ++i) {
		bool change = false;
		for (int j = 0; j < m; ++j) {
			int u = E[j].u, v = E[j].v, w = E[j].w, t;
			if (len[u] < INT_MAX && (len[v] > (t = minTime(len[u], w, E[j].cnt, E[j].t)))) {
				if (t < INT_MAX) {
					len[v] = t;
					change = true;
				}
			}
			if (len[v] < INT_MAX && (len[u] > (t = minTime(len[v], w, E[j].cnt, E[j].t)))) {
				if (t < INT_MAX) {
					len[u] = t;
					change = true;
				}
			}
		}
		if (!change) {
			break;
		}
	}
	return len[end];
}

int main()
{
	int s, t;
	while (EOF != scanf("%d %d %d %d", &n, &m, &s, &t) && n > 0) {
		for (int i = 0; i < m; ++i) {
			scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].w);
			E[i].cnt = 0;
			char str[600], delimter[] = " ";
			char *ptr;
			gets(str);
			ptr = strtok(str, delimter);
			while (ptr) {
				E[i].t[E[i].cnt++] = atoi(ptr);
				ptr = strtok(NULL, delimter);
			}
		}
		int ans = bellman_ford(s, t);
		if (0 <= ans && ans < INT_MAX) {
			printf("%d\n", ans);
		} else {
			puts("*");
		}
	}
	return 0;
}

