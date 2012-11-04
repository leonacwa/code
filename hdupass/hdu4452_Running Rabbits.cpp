#include <cstdio>
#include <cstring>
#include <algorithm>

struct Rabbit {
	int d, s, t, x, y;
};
Rabbit tm, je;
int n;

int gd(char d) {
	if ('N' == d) return 0;
	if ('S' == d) return 1;
	if ('W' == d) return 2;
	if ('E' == d) return 3;
	return -1;
}

bool check_edge(Rabbit &r) {
	bool ch = false;
	if (r.d == 0 && r.x == 1) ch = true;
	if (r.d == 1 && r.x == n) ch = true;
	if (r.d == 2 && r.y == 1) ch = true;
	if (r.d == 3 && r.y == n) ch = true;
	if (ch) {
		//printf("edge %d %d, %d", r.x, r.y, r.d);
		if (r.d >= 2) r.d = 1 - (r.d - 2) + 2;
		else r.d = 1 - r.d;
		//printf(" %d\n", r.d);
	}
	return ch;
}


bool go(int d, int x, int y, int &x2, int &y2) {
	//printf("go %d: %d %d -> ", d, x, y);
	if (d == 0) {
		x2 = x - 1, y2 = y;
	} else if (d == 1) {
		x2 = x + 1, y2 = y;
	} else if (d == 2) {
		x2 = x, y2 = y - 1;
	} else if (d == 3) {
		x2 = x, y2 = y + 1;
	} else {
		return false;
	}
	if (1 <= x2 && x2 <= n && 1 <= y2 && y2 <= n) {
	//printf("%d %d\n", x2, y2);
		return true;
	}
	puts("");
	return false;
}

void go(Rabbit &r) {
	for (int i = 0; i < r.s; ++i) {
		while ( check_edge(r) ) ;
		go(r.d, r.x, r.y, r.x, r.y);
	}
}

void turn_left(Rabbit &r) {
	//printf("tl %d -> ", r.d);
	if (r.d == 0) r.d = 2;
	else if (r.d == 1) r.d = 3;
	else if (r.d == 2) r.d = 1;
	else if (r.d == 3) r.d = 0;
	//printf("%d\n", r.d);
}

int main() {
	char str[32];
	while (EOF != scanf("%d", &n)) {
		if (n == 0) break;
		scanf("%s%d%d", str, &tm.s, &tm.t);
		tm.d = gd(str[0]);
		tm.x = 1, tm.y = 1;
		scanf("%s%d%d", str, &je.s, &je.t);
		je.d = gd(str[0]);
		je.x = n, je.y = n;
		int k;
		scanf("%d", &k);
		for (int nt = 1; nt <= k; ++nt) {
			go(tm);
			go(je);
			if (tm.x == je.x && tm.y == je.y) {
				std::swap(tm.d, je.d);
		//		printf("encounter\n");
			} else {
				if (nt % tm.t == 0) turn_left(tm);
				if (nt % je.t == 0) turn_left(je);
			}
			//puts("");
		}
		printf("%d %d\n", tm.x, tm.y);
		printf("%d %d\n", je.x, je.y);
		//puts("******************************************");
	}
	return 0;
}
