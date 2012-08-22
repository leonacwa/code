/*
ID:freeleo1
LANG:C
TASK:friday
*/
#include <stdio.h>
int mon[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int day[8] = {0};

int is_leap_year(int y)
{
	if (y % 100 == 0 ) 
		return y % 400 == 0;
	else return y % 4 == 0;
}
int main()
{
	int y, m, d, date, n;
	freopen("friday.in", "r", stdin);
	freopen("friday.out", "w", stdout);
	scanf("%d", &n);
	y = 1900;
	m = 1;
	date = 13;
	while (y < 1900+n) {
		day[(date-1)%7 + 1]++;	
		date += mon[m];
		if (is_leap_year(y) && m == 2) date++;
		m++;
		if (m == 13) {
			m = 1;
			y++;
		}
	}
	for (d = 6; d < 6+6; ++d) printf("%d ", day[(d-1)%7+1]);
	printf("%d\n", day[(d-1)%7+1]);
	fclose(stdout);
	return 0;
}

