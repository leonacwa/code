#include <stdio.h>
#include <math.h>


int ans[100000+5][2];

int gcd(int a, int b)
{
	int t;
	while (b) {
		t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int main()
{
	int caseN = 0;
	int c;
	while (EOF != scanf("%d", &c) && c > 0) {
		int n = 0;
		if (c % 2 == 0 || c*c%4 != 1) {
			n = 0;
		} else {
			int up = (int)(sqrt(c*c/2));
			for (int a = 3; a <= up; a++) {
				int b = (int)(sqrt(c*c-a*a));
				if (((a%2==1 && b%2==0) || (a%2==0 && b%2==1)) && c*c == a*a+b*b && 1 == gcd(gcd(a, b), c)) {
					ans[n][0] = a;
					ans[n][1] = b;
					n++;
				}
				b++;
				if (((a%2==1 && b%2==0) || (a%2==0 && b%2==1)) && c*c == a*a+b*b && 1 == gcd(gcd(a, b), c)) {
					ans[n][0] = a;
					ans[n][1] = b;
					n++;
				}	
			}
		}
		caseN++;
		printf("Case %d:\n", caseN);
		printf("There are %d solution(s).\n", n);
		for (int i = 0; i < n; i++) {
			printf("%d^2 + %d^2 = %d^2\n", ans[i][0], ans[i][1], c);
		}
		printf("\n");
	}
	return 0;
}

