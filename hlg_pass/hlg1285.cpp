#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Card {
	int a, b;
	bool operator < (const Card &bb) const {
		if (a != bb.a) {
			return a > bb.a;
		}
		return b > bb.b;
	}
};

struct Pai {
	int type;
	Card sign;
	Card c[6];
	bool operator < (const Pai &bb) const {
		if (type != bb.type) {
			return type > bb.type;
		}
		return sign < bb.sign;
	}
};
Pai p1, p2;
int ch_n[256];

void deal(Pai &p)
{
	Card *c;
	c = p.c;
	sort(c, c+5);
	if (c[0].a-1 == c[1].a && c[1].a-1 == c[2].a && c[2].a-1 == c[3].a && c[3].a-1 == c[4].a &&
		c[0].b == c[1].b && c[1].b == c[2].b && c[2].b == c[3].b && c[3].b == c[4].b ) {
		p.type = 5;
		p.sign = c[0];
		return;
	}
	if ((c[0].a == c[1].a && c[1].a == c[2].a && c[2].a == c[3].a) ||
		(c[1].a == c[2].a && c[2].a == c[3].a && c[3].a == c[4].a)) {
		p.type = 4;
		if (c[0].a == c[1].a) {
			p.sign = c[0];
		} else {
			p.sign = c[1];
		}
		return;
	}
	if ((c[0].a == c[1].a && c[1].a == c[2].a && c[3].a == c[4].a) ||
		(c[0].a == c[1].a && c[2].a == c[3].a && c[3].a == c[4].a)) {
		p.type = 3;
		if (c[1].a == c[2].a) {
			p.sign = c[0];
		} else {
			p.sign = c[2];
		}
		return;
	}
	if (c[0].b == c[1].b && c[1].b == c[2].b && c[2].b == c[3].b && c[3].b == c[4].b ) {
		p.type = 2;
		p.sign = c[0];
		return;
	}
	p.type = 1;
	p.sign = c[0];
}

int main()
{
	ch_n['2'] = 2;
	ch_n['3'] = 3;
	ch_n['4'] = 4;
	ch_n['5'] = 5;
	ch_n['6'] = 6;
	ch_n['7'] = 7;
	ch_n['8'] = 8;
	ch_n['9'] = 9;
	ch_n['T'] = 10;
	ch_n['J'] = 11;
	ch_n['Q'] = 12;
	ch_n['K'] = 13;
	ch_n['A'] = 14;
	ch_n['D'] = 1;
	ch_n['C'] = 2;
	ch_n['H'] = 3;
	ch_n['S'] = 4;
	int nCase;
	char s[10];
	scanf("%d", &nCase);
	while (nCase--) {
		for (int i = 0; i < 5; i++) {
			scanf("%s", s);
			p1.c[i].a = ch_n[s[0]];
			p1.c[i].b = ch_n[s[1]];
		}
		for (int i = 0; i < 5; i++) {
			scanf("%s", s);
			p2.c[i].a = ch_n[s[0]];
			p2.c[i].b = ch_n[s[1]];
		}
		deal(p1);
		deal(p2);
		if (p1 < p2) {
			puts("first");
		} else if (p2 < p1) {
			puts("second");
		} else {
			puts("equal");
		}
	}
	return 0;
}

