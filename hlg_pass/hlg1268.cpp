#include <stdio.h>

int main()
{
	int n;
	while (~scanf("%d", &n)) {
		long long s = 1;
		s <<= n;
		--s;
		printf("%lld years %lld days %lld hours %lld minute %lld seconds\n", s / (60*60*24*365), (s / (60*60*24)) % 365, (s / (60*60)) % 24, s / 60 % 60,  s % 60);
	}
	return 0;
}

