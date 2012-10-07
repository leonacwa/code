#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct Patient {
	int id, priority;
};

bool comp(const Patient &a, const Patient &b) {
	return a.priority < b.priority;
}
void swap(Patient &a, Patient &b) {
	Patient t = a;
	a = b;
	b = t;
}

void make_heap(Patient *first, Patient *last)
{
	if (first == last || first + 1 == last) return;
	Patient * ptr = first - 1;
	int n = last - first;
	for (int i = n / 2; i > 0; --i) {
		int p = i;
		while (p * 2 <= n) {
			int c = p * 2;
			if (c < n) {
				if (!comp(ptr[c], ptr[c+1])) {
					++c;
				}
			}
			if (!comp(ptr[p], ptr[c])) {
				swap(ptr[p], ptr[c]);
				p = c;
			} else {
				break;
			}
		}
	}
}

void pop_heap(Patient *first, Patient *last)
{
	if (first == last || first + 1 == last) return;
	Patient * ptr = first - 1;
	int n = last - first;
	swap(ptr[1], ptr[n]);
	--n;
	int p = 1;
	while (p * 2 <= n) {
		int c = p * 2;
		if (c < n) {
			if (!comp(ptr[c], ptr[c+1])) {
				++c;
			}
		}
		if (!comp(ptr[p], ptr[c])) {
			swap(ptr[p], ptr[c]);
			p = c;
		} else {
			break;
		}
	}
}

void push_heap(Patient *first, Patient *last)
{
	if (first == last || first + 1 == last) return;
	Patient * ptr = first - 1;
	int n = last - first;
	int c = n;
	while (c > 1) {
		int p = c / 2;
		if (!comp(ptr[p], ptr[c])) {
			swap(ptr[p], ptr[c]);
			c = p;
		} else {
			break;
		}
	}
}

int main()
{
	int cnt = 0;
	int id, pri;
	Patient p[1024];
	while (cin >> id >> pri) {
		if (id == -1 && pri == -1) break;
		p[cnt].id = id;
		p[cnt].priority = pri;
		++cnt;
	}
	make_heap(p, p + cnt);
	while (cnt > 0) {
		cout << p[0].id << endl;
		pop_heap(p, p + cnt);
		--cnt;
	}
	return 0;
}

