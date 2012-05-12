#include <stdio.h>
int main()
{
	int n, b;
	while (~scanf("%d", &n)) {
		switch (n)
		{
			case 1: b = 5; break;
			case 2: b = 6; break;
			case 3: b = 7; break;
			case 4: b = 18; break;
			case 5: b = 1; break;
			case 6: b = 2; break;
			case 7: b = 3; break;
		}
		printf("%d\n", b);
	}
	return 0;
}

