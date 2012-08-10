#include <cstdio>
#include <iostream>
using namespace std;

struct Date {
	const int month[13];
	int y, m, d, w;

	bool isLeapYear() {
		return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
	}
	void inc()
	{
		++d;
		if (d == (month[m] + ((m == 2 && isLeapYear()) ? 1 : 0))) {
			d = 1;
			++m;
			if (m == 12) {
				m = 1;
				++y;
			}
		}
		w = (w + 1) % 7;
	}
	void dec()
	{
		--d;
		if (d == 0) {
			--m;
			if (m == 0) {
				--y;
				m = 12;
			}
			d = month[m] + ((m == 2 && isLeapYear()) ? 1 : 0);
		}
		w = (w - 1) % 7;
	}

	bool operator == (const Date& b) const {
		return y == b.y && m == b.m && d == b.d;
	}
	bool operator < (const Date& b) const {
		if (y != b.y) return y < b.y;
		if (m != b.m) return m < b.m;
		return d < b.d;
	}
};

const int Date::month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char space4[] = "    ";
const char space5[] = "     ";

int main()
{
	Date sd;
	sd.y = 2011;
	sd.m = 8;
	sd.d = 1;
	sd.w = 0;
	while (EOF != scanf("%d %d", &y, &m)) {
		Date date;
		Date wd = sd;
		date.y = y;
		date.m = m;
		date.d = 1;
		if (date < wd) {
			while (date < wd) {
				wd.dec();
			}
		} else {
			while (wd < date) {
				wd.inc();
			}
		}
		printf("Case %d:\n", ++nCase);
		printf(" Sun  Mon  Tue  Web  Thu  Fri  Sat\n");
		for (int i = 0; i < wd.w) {
			printf("%s", );
		}
		while (wd.m == m) {
		}
	}
	return 0;
}

