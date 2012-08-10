#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

const int NN = 1005;
struct Elem {
	char name[32];
	char type[32];
	int ID, price, qual;
};
int n, b;
map<string, int> start;
map<string, int> name_id;
char name[NN][32];
int ID;
Elem E[NN];
int qual[NN];

bool cmpE(const Elem &a, const Elem &b) {
	int r = strcmp(a.name, b.name);
	if (r != 0) return r < 0;
	if (a.price != b.price) return a.price < b.price;
	return a.qual > b.qual;
}

bool check(int q)
{
	int i, s = b;
	for (i = 1; i <= ID; ++i) {
		if (s < 0) break;
		bool get = false;
		for (int j = start[name[i]]; j < n && E[j].ID == i; ++j) {
			if (E[j].qual >= q) {
				s -= E[j].price;
				get = true;
				break;
			}
		}
		if (!get) return false;
	}
	return s >= 0 && i > ID;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--) {
		ID = 0;
		start.clear();
		name_id.clear();
		scanf("%d %d", &n, &b);
		for (int i = 0; i < n; ++i) {
			scanf("%s %s %d %d", E[i].name, E[i].type, &E[i].price, &E[i].qual);
			qual[i] = E[i].qual;
			if (0 == name_id[E[i].name]) {
				name_id[E[i].name] = ++ID;
				strcpy(name[ID], E[i].name);
			}
			E[i].ID = ID;
		}
		sort(E, E+n, cmpE);
		sort(qual, qual+n);
		char type[24] = "";
		for (int i = 0; i < n; ++i) {
			if (strcmp(type, E[i].name) != 0) {
				strcpy(type, E[i].name);
				start[type] = i;
			}
		}
		int l = 0, r = n - 1, m;
		while (l < r - 1) {
			m = l + (r - l) / 2;
			if (check(qual[m])) {
				l = m;
			} else {
				r = m - 1;
			}
		}
		if (check(qual[r])) {
			m = r;
		} else {
			m = l;
		}
		printf("%d\n", qual[m]);;
	}
	return 0;
}

