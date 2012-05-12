#include <string.h>
#include<iostream>
using namespace std;
#define MAXN 1024

void init(int a[]) {
	memset(a, 0, sizeof(a[0])*MAXN);
}
void add(int a[], int b[], int c[]) {
	int i, len = max(a[0], b[0]);
	init(c);
	for (i = 1; i <= len; ++i) {
		if (i <= a[0]) c[i] += a[i];
		if (i <= b[0]) c[i] += b[i];
		if (c[i] >= 10) {
			c[i+1] += c[i] / 10;
			c[i] %= 10;
		}
	}
	if (c[len+1] > 0) {
		len++;
	}
	c[0] = len;
}

void input(int a[]) {
	int j;
	char str[MAXN];
	cin >> str;
	a[0] = strlen(str);
	for (j = a[0] - 1; j >= 0; --j) {
		a[a[0] - j] = str[j] - '0';
	}
}
void print(int a[]) {
	int i;
	for (i = a[0]; i >= 1; --i) {
		cout << a[i];
	}
}

int main()
{
	int a[MAXN], b[MAXN], c[MAXN];
	char str[MAXN];
	int i, n;
	cin >> n;
	for (i = 1; i <= n; ++i) {
		input(a);
		input(b);
		cout << "Case " << i << ":" << endl;
		print(a);
		cout<< " + ";
		print(b);
		cout << " = ";
		add(a, b, c);
		print(c);
		cout << endl;
		if (i < n) cout << endl;
	}
	return 0;
}