/* ZOJ 1007 Numerical Summation of a Series
 * 按照题目要求把式子化成精度更高的写法，注意处理最后的无穷项，可以直接加上一个数
 * */
#include <stdio.h>
#include <math.h>

int main()
{
	 double x = 0.0, sum, limit;
	for (x = 0.0; x <= 2.0 + 1e-8; x += 0.001) {
		sum = 0.0;
		limit = 3e4 + 10;
		for (int k = 1; k < limit; ++k) {
			sum += (1 - x) / ((k+x) * (k + 1) * k);
		}
		sum += 1.0 + (1-x) / (limit * limit * 2);
		printf("%5.3f %16.12f\n", x, sum);
	}
	return 0;
}

