/*
定义
　　对于任何正整数x,其约数的个数记做g(x).例如g(1)=1,g(6)=4.如果某个正整数x满足:对于任意i(0<i<x),都有g(i)<g(x),则称x为反素数.
性质
　　性质一:一个反素数的质因子必然是从2开始连续的质数.
　　性质二:p=2^t1*3^t2*5^t3*7^t4.....必然t1>=t2>=t3>=....
*/

const int pm[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int max_num, best_num, max_fp;

void anti_prime(int num, int a, int b, int limit)
{
	if (b > max_fp) {
		best_num = num;
		max_fp = b;
	} else if (b == max_fp && num < best_num) {
		best_num = num;
	}
	if (a >= 8) {
		return;
	}
	int tmp = num;
	for (int i = 1; i <= limit; i++) {
		tmp *= pm[a];
		if (tmp <= max_num) {
			anti_prime(tmp, a+1, b*(i+1), i);
		} else {
			break;
		}
	}
}