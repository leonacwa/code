// http://acm.hrbust.edu.cn/index.php?m=ProblemSet&a=submitCode&problem_id=1176
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000;

int r[MAXN+5];
struct Num {
	int v, c;
};
Num nn[MAXN+5];
int ans[MAXN+5][3];

inline bool cmpNum(const Num &a, const Num &b) {
	return a.c > b.c;
}

void make_heap(int f, int n) 
{
	int c = f * 2;
	Num tn = nn[f];
	while (c <= n) {
		if (c < n && cmpNum(nn[c+1], nn[c])) {
			c++;
		}
		if (cmpNum(nn[c], tn)){
			nn[f] = nn[c];
			f = c;
			c = f * 2;
		} else {
			break;
		}
	}
	nn[f] = tn;
}

void add(Num tn, int &p)
{
	p++;
	int c = p;
	while (c > 1 && cmpNum(tn, nn[c/2])) {
		nn[c] = nn[c/2];
		c /= 2;
	}
	nn[c] = tn;
}

Num pop(int &p)
{
	Num tn = nn[1];
	nn[1] = nn[p];
	p--;
	make_heap(1, p);
	return tn;
}

int main()
{
	int n = 19;
	srand(time(0));
	for (int i = 1; i <= n; i++) {
		nn[i].c = rand();
	}
	for (int i = n/2; i > 0; i--) {
		make_heap(i, n);
	}
	while (n >0) {
		Num t = pop(n);
		printf("%d ", t.c);
	}
	printf("\n");
	for (int i = 1; i <= n; i++) {
		Num t = nn[1];
		nn[1] = nn[n-i+1];
		nn[n-i+1] = t;
		make_heap(1, n-i);
		printf("%d ", t.c);
	}
	printf("\n");
	for (int i = n; i > 0;  i--) {
		printf("%d ", nn[i].c);
	}
	printf("\n\n");
	//--------------/
	
	for (int i = n/2; i > 0; i--) {
		make_heap(i, n);
	}
	for (int i = 0; i < 3; i++) {
		Num t;
		t.c = rand();
		add(t, n);
	}
	for (int i = 1; i <= n; i++) {
		Num t = nn[1];
		nn[1] = nn[n-i+1];
		nn[n-i+1] = t;
		make_heap(1, n-i);
		printf("%d ", t.c);
	}
	printf("\n");
	for (int i = n; i > 0; i--) {
		printf("%d ", nn[i].c);
	}	
	return 0;
}

