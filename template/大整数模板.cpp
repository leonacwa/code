/* 大数
 * */

struct Integer {
	int l;
	int a[100];
	void clear() {
		memset(a, 0, sizeof(a));
		l = 1;
	}
};

void Add(Integer &a, Integer &b)
{
	for (int i = 0; i < b.l; ++i) {
		if (i < a.l) {
			a.a[i] += b.a[i];
		} else {
			a.a[i] = b.a[i];
		}
	}
	if (a.l < b.l) a.l = b.l;
	for (int i = 0; i < a.l; ++i) {
		if (a.a[i] >= 10) {
			a.a[i+1] += a.a[i] / 10;
			a.a[i] %= 10;
		}
	}
	while (a.a[a.l] >= 10) {
		a.a[a.l+1] += a.a[a.l] / 10;
		a.a[a.l] %= 10;
		a.l++;
	}
	if (a.a[a.l] > 0) a.l++;
}

void Mul(Integer &a, int n, Integer &b)
{
	if (&a == &b) puts("error");
	b.clear();
	if (a.l == 0 || n == 0 || (a.l == 1 && a.a[0] == 0)) {
		return;
	}
	for (int i = 0; i < a.l; ++i) b.a[i] = a.a[i] * n;
	for (int i = 0; i < a.l; ++i) {
		if (b.a[i] >= 10) {
			b.a[i+1] += b.a[i] / 10;
			b.a[i] %= 10;
		}
	}
	b.l = a.l;
	while (b.a[b.l] >= 10) {
		b.a[b.l+1] = b.a[b.l] / 10;
		b.a[b.l] %= 10;
		b.l++;
	}
	if (b.a[b.l] > 0) ++b.l;
}

void Print(const Integer &a) {
	for (int i = a.l - 1; i >= 0; --i) printf("%d", a.a[i]);
}

