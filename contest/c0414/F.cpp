#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int NN = 200005;
char str[NN], ans[NN];

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		scanf("%s", str);
		int ls = strlen(str);
		ans[0] = 0;
		int i, j, k, p = 0;
		bool yes = true;
		for (i = 0; i < ls; ++i) {
			k = -1;
			for (j = i; j < ls; ++j) {
				ans[p++] = str[j];
				if (str[j] == '.' && k == -1) {
					k = j;
				}
				if (k != -1 && str[j+1] == '.') {
					j -= 1;
					p -= 1;
					break;
				}
				if (k > -1 && j - k == 3) {
					break;
				}
			}
			if (j == ls) --j;
			if (k != -1 && 1 <= k - i  && k - i <= 8 && 1 <= j - k && j - k <= 3) {
				ans[p++] = '\n';
				ans[p] = 0;
				i = j;
			} else {
				yes = false;
				goto PrintAns;
			}
		}
PrintAns:
		if (yes) {
			printf("YES\n%s", ans);
		} else {
			printf("NO\n");
		}
	}
	return 0;
}

