#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
using namespace std;

struct Node {
	int b, r;
	char name[21];
};

bool cmpb(const Node &A, const Node &B)
{
	if (A.b != B.b) return A.b < B.b;
	return strcmp(A.name, B.name) > 0;
}
bool cmpr(const Node &a, const Node &b)
{
	if (a.r != b.r) return a.r < b.r;
	return strcmp(a.name, b.name) > 0;
}
Node A[10000+1], B[1000+1];
int nA, nB;
int n, m;

int main()
{
	while (EOF != scanf("%d %d", &m, &n)) {
		nB = 0;
		nA = 0;
		make_heap(A, A+nA, cmpb);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				scanf("%s %d %d", A[nA].name, &A[nA].b, &A[nA].r);
				nA++;
				push_heap(A, A+nA, cmpb);
			}
			for (int j = 0; j < 5; ++j) {
				B[nB++] = A[0];
				pop_heap(A, A+nA, cmpb);
				nA--;
			}
		}
		make_heap(B, B+nB, cmpr);
		for (int i = 0; i < 5; ++i) {
			puts(B[0].name);
			pop_heap(B, B+nB, cmpr);
			nB--;
		}
	}
	return 0;
}
