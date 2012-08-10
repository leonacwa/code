#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node {
	int b, r;
	char name[26];
};

bool cmpb(const Node &a, const Node &b)
{
	if (a.b != b.b) return a.b > b.b;
	//if (a.r != b.r) return a.r > b.r;
	return strcmp(a.name, b.name) < 0;
}
bool cmpr(const Node &a, const Node &b)
{
	if (a.r != b.r) return a.r > b.r;
	//if (a.b != b.b) return a.b > b.b;
	return strcmp(a.name, b.name) < 0;
}
const int NN = 10000 * 2;
Node A[NN];
int nA, nB;
int n, m;

int main()
{
	while (EOF != scanf("%d %d", &m, &n)) {
		nB = 0;
		nA = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%s %d %d", A[nA].name, &A[nA].b, &A[nA].r);
				nA++;
			}
			sort(A+nB, A+nA, cmpb);
			nB += 5;
		}
		sort(A, A+nB, cmpr);
		for (int i = 0; i < 5; ++i) {
			puts(A[i].name);
		}
	}
	return 0;
}

