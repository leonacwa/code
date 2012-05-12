/*
ID:freeleo1
LANG:C
TASK:namenum 
*/
#include <stdio.h>
/*   
2: A,B,C     5: J,K,L    8: T,U,V
3: D,E,F     6: M,N,O    9: W,X,Y          
4: G,H,I     7: P,R,S
*/
int num[26] = {2,2,2,  3,3,3,  4,4,4, 5,5,5,  6,6,6,  7,0,7,7,  8,8,8,  9,9,9, 0};
int main()
{
	freopen("namenum.in", "r", stdin);
	freopen("namenum.out", "w", stdout);
	int i, j;
	char no[32], na[32];
	scanf("%s", no);
	for (i = 0; no[i]; ++i) no[i] -= '0';
	freopen("dict.txt", "r", stdin);
	j = 0;
	while (1 == scanf("%s", na)) {
		for (i = 0; no[i] && na[i] && no[i] == num[na[i]-'A']; ++i)  ;
		if (no[i]==0 && na[i]==0) printf("%s\n", na), j++;
	}
	if (j == 0 ) printf("NONE\n");
	fclose(stdout);
	return 0;
}

