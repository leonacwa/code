/*
ID:freeleo1
LANG:C
TASK:gift1 
*/
#include <stdio.h>
#include <string.h>
#define MAXN 256

char name[MAXN][16];
int money[MAXN];
int n;

int find(const char *s)
{
	int i;
	for (i = 0; i < n; ++i) if (0 == strcmp(name[i], s)) return i;
	return -1;
}
int main()
{
	int i, j, id, id2, a, b;
	char str[256];
	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%s", name[i]);
	for (i = 0; i < n; ++i) {
	       	scanf("%s %d %d", str, & a, &b);
		id = find(str);
		//money[id] += a;
		for (j = 0; j < b; ++j) {
			scanf("%s", str);				
			id2 = find(str);
			money[id2] += a / b;
			money[id] -= a / b;
		}
	}
	for (i = 0; i < n; ++i) printf("%s %d\n", name[i], money[i]);
	fclose(stdout);
	return 0;
}

