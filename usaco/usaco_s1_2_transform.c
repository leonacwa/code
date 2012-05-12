/*
ID:freeleo1
LANG:C
TASK:transform
*/
#include <stdio.h>

char map[4][11][11];
int n;

void ratate(char a[11][11], char b[11][11])
{
	int i, j;
	for (i = 0; i < n; ++i)  	for (j = 0; j < n; ++j)
		b[j][n-i-1] = a[i][j];
}
void reflect(char a[11][11], char b[11][11])
{
	int i, j;
	for (i = 0; i < n; ++i) for (j = 0; j < n; ++j)
		b[i][n-1-j] = a[i][j];
}
int same(char a[11][11], char b[11][11])
{
	int i;
	for (i = 0; i < n; ++i) if (strcmp(a[i], b[i])) return 0;
	return 1;
}
void mapcpy(char a[11][11], char b[11][11])
{
	int i, j;
	if ((char*)a == (char*)b) return;
	for (i = 0; i < n; ++i) for (j = 0; j < n; ++j) b[i][j] = a[i][j];
}

int main()
{
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
	int i, ans = 7;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) scanf("%s", map[2][i]);
	for (i = 0; i < n; ++i) scanf("%s", map[3][i]);
	mapcpy(map[2], map[0]);
	for (i = 0; i < 3; ++i) {
		ratate(map[i%2], map[(i+1)%2]);
		if (same(map[3], map[(i+1)%2])) {
			ans = i+1;
		       	break;
		}
	}
	mapcpy(map[2],  map[0]);
	if (ans == 7) {
		reflect(map[0], map[1]);
		if (same(map[1], map[3])) ans = 4;
		else {
			for (i = 1; i <= 3; ++i) {
				ratate(map[i%2], map[(i+1)%2]);
				if (same(map[(i+1)%2], map[3])) {
					ans = 5; 
					break;
				}
			}
		}
	}
	if(ans == 7 && same(map[2], map[3])) ans = 6;
	printf("%d\n", ans);
	fclose(stdout);
	return 0;
}

