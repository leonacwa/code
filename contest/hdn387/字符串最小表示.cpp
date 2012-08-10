// 
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
void Minrepress( char *s , char *str ) {
    int i = 0 , j = 1 , count = 0 , t ;
    int len=strlen(s);
    while( i < len && j < len && count < len)
    {
        t=s[(i + count)%len] -s[( j + count)%len] ;
        if( t==0)
            count ++ ;
       else
       {
            if(t>0)
             i += count + 1 ;
            else
             j += count + 1 ;
            if( i == j ) j++ ;
            count = 0 ;
        }
    }
    int Size = 0 ;
    for( j = min(i,j) ; Size < len ; j ++ ,Size++)
        str[ Size ] = s[ j%len ] ;
    str[ Size ] = '\0' ;
}
char stra[300005];
char strb[300005];
int main() {
	while (scanf("%s", stra) != EOF) {
		int l = strlen(stra);
		for (int i = 0; i < l; i++) {
			strb[i] = (stra[(i + 1) % l] + 8 - stra[i]) % 8 + '0';
		}
		strb[l] = 0;
		Minrepress(strb, stra);
		puts(stra);
	}
	return 0;
}