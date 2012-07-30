/*
����
���������κ�������x,��Լ���ĸ�������g(x).����g(1)=1,g(6)=4.���ĳ��������x����:��������i(0<i<x),����g(i)<g(x),���xΪ������.
����
��������һ:һ���������������ӱ�Ȼ�Ǵ�2��ʼ����������.
�������ʶ�:p=2^t1*3^t2*5^t3*7^t4.....��Ȼt1>=t2>=t3>=....
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