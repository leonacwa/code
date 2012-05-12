// 围困
#include <stdio.h>

int sign(int x) {
	
	if (x) 
		return x > 0 ? 1 : -1;
	return 0;
}

int cross(int x1, int y1, int x2, int y2) {
	return x1*y2 - x2*y1;
}

int main()
{
	int x[4], y[4];
	int i;
	int flag;
	while (EOF != scanf("%d %d %d %d %d %d %d %d", x+0, y+0, x+1, y+1, x+2, y+2, x+3, y+3)) {
		flag = 1;
		for (i = 0; flag && i < 3; ++i) {
			flag = (sign(cross(x[(i+1)%3]-x[i], y[(i+1)%3]-y[i], x[(3+i-1)%3]-x[i], y[(3+i-1)%3]-y[i])) 
			       == sign(cross(x[3]-x[i], y[3]-y[i], x[(3+i-1)%3]-x[i], y[(3+i-1)%3]-y[i])));
		}
		printf("%s\n", flag?"Die" : "Live");
	}
	return 0;
}