#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;

const int N = 1024+1;
int c[N][N];
int Row = 1024, Col = 1024;

inline int Lowbit(const int &x){// x > 0
	return x&(-x);
}
int Sum(int i, int j){
	int tempj, sum = 0;
	while( i > 0 ){
		tempj = j;
		while( tempj > 0 ){
			sum += c[i][tempj];
			tempj -= Lowbit(tempj);
		}
		i -= Lowbit(i);
	}
	return sum;
}

void Update(int i, int j, int num){
	int tempj;
	while( i <= Row ){
		tempj = j;
		while( tempj <= Col ){
			c[i][tempj] += num;
			tempj += Lowbit(tempj);
		}
		i += Lowbit(i);
	}
}

int MatSum(int x1, int y1, int x2, int y2)
{
	return Sum(x2, y2) - Sum(x2, y1-1) - Sum(x1-1, y2) + Sum(x1-1, y1-1);
}
int main() {
	int n;
	while (EOF != scanf("%d", &n)) {
		memset(c, 0, sizeof(c));
		int rch = 0, cch = 0;
		for (int i = 1; i <= Row; ++i) {
			cch = rch;
			for (int j = 1; j <= Col; ++j) {
				if (cch == 0) Update(i, j, 1);
				//else Update(B, i, j, 1);
				cch = 1- cch;
			}
			rch = 1- rch;
		}
		//puts("init end");
		for (int i = 0; i < n; ++i) {
			char cmd[32];
			scanf("%s", cmd);
			if (cmd[0] == 'R') {
				int x1, x2, y1, y2;
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				int a = MatSum(x1, y1, x2, y2);
				int b = (x2 - x1 + 1) * (y2 - y1 + 1) - a;
				printf("%d %d\n", a, b);
			} else if (cmd[0] == 'A') {
				int x, y;
				scanf("%d%d", &x, &y);
				if (MatSum(x, y, x, y) == 0) {
					Update(x, y, 1);
				}
			} else if (cmd[0] == 'B') {
				int x, y;
				scanf("%d%d", &x, &y);
				if (MatSum(x, y, x, y) == 1) {
					Update(x, y, -1);
				}
			} else {while(1) ; puts("error");}
		}
	}
	return 0;
}
