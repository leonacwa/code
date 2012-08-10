#include <cstdio>
#include <cstring>
#include <climits>

const int INF = INT_MAX;
int mem[1000010];
int que[2000010];

int main()
{
	int f, s, g, u, d;
	while (EOF != scanf("%d%d%d%d%d", &f, &s, &g, &u, &d)) {
		for (int i = 0; i <= f; ++i) mem[i] = INF;
		int *fr = que, *ta = que;
		mem[s] = 0;
		*ta++ = s;
		while (fr < ta) {
			int c = *fr++, t, sp;
			sp = mem[c] + 1;
			t = c + u;
			//if (t >= f) t = f;
			if (t <= f && mem[t] > sp) {
				mem[t] = sp;
				*ta++ = t;
			}
			t = c - d;
			//if (t < 1) t = 1;
			if (t >= 1 && mem[t] > sp) {
				mem[t] = sp;
				*ta++ = t;
			}
			if (mem[g] < INF) break;
		}
		if (mem[g] < INF) printf("%d\n", mem[g]);
		else puts("use the stairs");
	}
	return 0;
}
