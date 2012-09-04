/* February 29
 * 判断两个日期间有多少个闰年
 * */
#include <cstdio>
#include <cstring>

const int month_day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date {
	int y, m, d;
	bool operator < (const Date &b) const {
		if (y != b.y) return y < b.y;
		if (m != b.m) return m < b.m;
		return d < b.d;
	}
bool is_leap_year() const{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) ;
}
	void dec() {
		--d;
		if (d == 0) {
			--m;
			if (m == 0) {
				m = 12;
				--y;
			}
			d = month_day[m-1] + (is_leap_year() && m == 2 && d == 0 ? 1 : 0);
		}
	}
	void out() const {
		//printf("%d %d %d\n", m, d, y);
	}
};

int count_leap_year(const Date a) {
	int ret = a.y / 4 - a.y / 100 + a.y / 400;
	if (a.is_leap_year() && (a.m < 2 || (a.m == 2 && a.d < 29))) --ret;
	//printf("cly %d %d %d : %d\n", a.m, a.d, a.y, ret);
	return ret;
}

int get_month(const char *s) {
	static const char *month_str[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	for (int i = 0; i < 12; ++i) {
		if (0 == strcmp(s, month_str[i])) return i + 1;
	}
	for(;;);
	return -1;
}

void get_date(Date &a) {
	char str[64];
	scanf("%s %d, %d\n", str, &a.d, &a.y);
	a.m = get_month(str);
}

int main() {
	int runs, run = 0;
	scanf("%d", &runs);
	while (runs--) {
		Date a, b;
		get_date(a);
		get_date(b);
		if (b < a) {
			Date c = a;
			a = b;
			b = c;
		}
		a.dec();
		int ans = count_leap_year(b) - count_leap_year(a);
		printf("Case %d: %d\n", ++run, ans);
	}
	return 0;
}
