/*
ID:freeleo1
LANG:C
TASK:test
*/
#include <stdio.h>
int main()
{
	FILE *fin = fopen("test.in", "r");
	FILE *fout = fopen("test.out", "w");
	int a, b;
	fscanf(fin, "%d %d", &a, &b);
	fprintf(fout, "%d\n", a+b);
	fclose(fout);
	//exit(0);
	return 0;
}
