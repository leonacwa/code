#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 205;
char s1[NN], s2[NN], s3[2*NN];
bool f[NN][NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	for (int nCase = 1; nCase <= nTest; ++nCase) {
		scanf("%s %s %s", s1+1, s2+1, s3+1);
		int l1 = strlen(s1+1), l2 = strlen(s2+1);
		f[0][0] = true;
		for (int i = 1; i <= l1; ++i) {
			f[i][0] = s3[i] == s1[i];
			f[0][i] = s3[i] == s2[i];
		}
		for  (int i = 1; i <= l1; ++i) {
			for (int j = 1; j <= l2; ++j) {
				f[i][j] = (f[i-1][j] && (s3[i+j] == s1[i])) || (f[i][j-1] && (s3[i+j] == s2[j]));
			}
		}
		printf("Data set %d: %s\n", nCase, f[l1][l2] ? "yes" : "no");
	}
	return 0;
}

