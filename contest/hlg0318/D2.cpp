#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
	int b, r;
	char name[26];

	bool operator < (const Node &B) const
	{
		if (b != B.b) return b < B.b;
		//if (a.r != b.r) return a.r > b.r;
		return strcmp(name, B.name) > 0;
	}
};

bool cmpr(const Node &a, const Node &b)
{
	if (a.r != b.r) return a.r > b.r;
	//if (a.b != b.b) return a.b > b.b;
	return strcmp(a.name, b.name) < 0;
}
const int NN = 1000 + 2;
Node A[NN];
int nA, nB;
int n, m;

int main()
{
	while (EOF != scanf("%d %d", &m, &n)) {
		nB = 0;
		nA = 0;
		priority_queue<Node> Q;
		for (int i = 0; i < m; ++i) {
			Node tn;
			for (int j = 0; j < n; ++j) {
				scanf("%s %d %d", tn.name, &tn.b, &tn.r);
				Q.push(tn);
			}
			for (int j = 0; j < 5; ++j) {
				A[nA++] = Q.top();
				Q.pop();
			}
		}
		nB = m * 5;
		sort(A, A+nB, cmpr);
		for (int i = 0; i < 5; ++i) {
			puts(A[i].name);
		}
	}
	return 0;
}

