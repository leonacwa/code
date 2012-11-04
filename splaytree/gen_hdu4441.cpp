#include <cstdio>
#include <cstring>
#include <ctime>
#include <set>
using namespace std;

template <const int MAXN>
struct TreeArray {
	int c[MAXN];
#define lowbit(x) ((x)&(-x))
	void add(int i, int v) {
		for (; i < MAXN; i += lowbit(i)) {
			c[i] += v;
		}
	}
	int sum(int i) {
		int s = 0;
		for (; i > 0; i -= lowbit(i)) {
			s += c[i];
		}
		return s;
	}
	int get_minp() {
		int l = 1, r = MAXN - 1;
		while (l < r) {
			int m = (l + r) >> 1;
			if (sum(m) >= 1) {
				r = m;
			} else {
				l = m + 1;
			}
		}
		return l;
	}
};

TreeArray<100005> ta;
set<int> ss;

void data(int n) {
	int len = 0;
	printf("%d\n", n);
	ss.clear();
	memset(ta.c, 0, sizeof(ta.c));
	for (int i = 1; i <= n; ++i) ta.add(i, 1);
	for (int i = 0; i < n; ++i) {
		int p = rand() % 3;
		if (p == 0 || len == 0) {
			printf("insert %d\n", rand() % (len+1));
			len += 2;
			int a = ta.get_minp();
			ta.add(a, -1);
			ss.insert(a);
		} else {
			int b = rand() % ss.size();
			set<int>::iterator it = ss.begin();
			for (int i = 1; i < b; ++i) ++it;
			if (p == 1) {
				printf("remove %d\n", *it);
				ta.add(*it, 1);
				ss.erase(it);
				len -= 2;
			} else {
				printf("query %d\n", *it);
			}
		}
	}
}

int main() {
	srand(time(0));
	data(100000);
	return 0;
}
