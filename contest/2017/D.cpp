#include <stdio.h>
#include <queue>
#include <iostream>
using namespace std;

const int MAXN = 200;

struct People {
	char name[32];
	bool v;
	int next;
};
People p[MAXN];
int N, M, D;

int main()
{
	while (EOF != scanf("%d", &N)) {
		queue<People> Q;
		for (int i = 1; i <= N; i++) {
			scanf("%s", p[i].name);
			Q.push(p[i]);
		}
		scanf("%d,%d", &M, &D);
		for (int i = 1; i < M; i++) {
			People p1 = Q.front();
			Q.pop();
			Q.push(p1);
		}
		while (Q.empty() == false) {
			People p1 = Q.front();
			Q.pop();
			for (int i = 1; i < D; i++) {
				Q.push(p1);
				p1 = Q.front();
				Q.pop();
			}
			printf("%s\n", p1.name);
		}
	}
	return 0;
}

