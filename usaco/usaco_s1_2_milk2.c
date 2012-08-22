/*
ID:freeleo1
LANG:C
TASK:milk2 
*/
#include <stdio.h>
int f[1000000+1];
int find(int x)
{ 
	if (f[x] == x || f[x] == -1) return x;
	return f[x] = find(f[x]);
}

int main()
{
	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);
	int i, n, a1, a2, b, e, t, ed = 0;
	scanf("%d", &n);
	memset(f, -1, sizeof(f));
	for (i = 0; i < n; ++i) {
		scanf("%d %d", &b, &e);
		if (e > ed) ed = e;
		while (b < e) {
		    t = find(b); 
		    if (t < e) f[t] = e;
		    b = t + 1;
		}
	}
	a1 = a2 = t = 0;  
	for (i = 0; f[i] == -1 && i < ed; ++i) ; 
	for (; i < ed; ++i) {
		if (f[i] == -1) t++;
		else {
			e = find(i); 
			if (a1 < e - i) a1 = e - i;
			if (a2 < t) a2 = t;
			t = 0;
			i = e-1;
		}
	}
	if (a2 < t) a2 = t;
	printf("%d %d\n", a1, a2);
	fclose(stdout);
	return 0;
}

