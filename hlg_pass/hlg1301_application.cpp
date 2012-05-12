#include <stdio.h>

struct Date {
	static const int month[13];
	int y, m, d;

	bool isLeapYear() {
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}
	bool operator < (const Date &b) const {
		if (y != b.y) return y < b.y;
		if (m != b.m) return m < b.m;
		return d < b.d;
	}
	bool operator <= (const Date &b) const {
		if (y != b.y) return y < b.y;
		if (m != b.m) return m < b.m;
		return d <= b.d;
	}
	bool operator == (const Date &b) const {
		return y == b.y && m == b.m && d == b.d;
	}
	Date& operator ++ () {
		++d;
		if (d > month[m] + ((m == 2 && isLeapYear()) ? 1 : 0)) {
			d = 1;
			++m;
			if (m > 12) {
				m = 1;
				++y;
			}
		}
		return *this;
	}
	Date operator ++ (int) {
		++d;
		if (d > month[m] + ((m == 2 && isLeapYear()) ? 1 : 0)) {
			d = 1;
			++m;
			if (m > 12) {
				m = 1;
				++y;
			}
		}
		return *this;
	}
	Date& operator -- () {
		--d;
		if (d == 0) {
			--m;
			if (m == 0) {
				--y;
				m = 12;
			}
			d = month[m] + (m == 2 && isLeapYear() ? 1 : 0);
		}
		return *this;
	}
	Date operator -- (int) {
		--d;
		if (d == 0) {
			--m;
			if (m == 0) {
				--y;
				m = 12;
			}
			d = month[m] + (m == 2 && isLeapYear() ? 1 : 0);
		}
		return *this;
	}
};
const int Date::month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int n;
Date trip[128][2];

bool inTrip(const Date& d)
{
	for (int i = 0; i < n; ++i) {
		if (trip[i][0] <= d && d <= trip[i][1]) {
			return true;
		}
	}
	return false;
}

int main()
{
	Date reside, land, start, app;
	int len, count;
	while (EOF != scanf("%d/%d/%d", &reside.m, &reside.d, &reside.y)) {
		scanf("%d/%d/%d", &land.m, &land.d, &land.y);
		scanf("%d", &n);
		
		for (int i = 0; i < n; ++i) {
			scanf("%d/%d/%d %d/%d/%d", &trip[i][0].m, &trip[i][0].d, &trip[i][0].y, &trip[i][1].m, &trip[i][1].d, &trip[i][1].y);
		}

		start = land;
		len = 0;
		count = 0;
		while (len < 730 && reside < start) {
			start--;
			if (!inTrip(start)) {
				++count;
			}
			++len;
		}
		app = land;
		for (; len < 365*3; ++len) {
			if (!inTrip(app)) {
				count += 2;
			}
			app++;
		}
		while (count < 1095*2) {
			len++;
			count += (inTrip(app)) ? 0 : 2;
			while (len > 1460) {
				if (!inTrip(start)) {
					count -= (start < land) ? 1 : 2;
				}
				start++;
				len--;
			}
			app++;
		}
		printf("%d/%d/%d\n", app.m, app.d, app.y);
	}
	return 0;
}

