#include <stdio.h>
int main()
{
	int v1, v2, v3;
	while (EOF != scanf("%d %d", &v1, &v2)) {
		if (v1 > 0) {
			v3 = v1 + v2;
		} else {
			v3 = v1 - v2;
		}
		printf("%d\n", v3);
	}
	return 0;
}

