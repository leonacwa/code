/* 求字符串的最小表示，时间复杂度O(n)
 * 周源的论文好像在写字符串下标时有错误了
*/

void Minrepress( char *s , char *str ) {
    int i = 0 , j = 1 , count = 0 , t ;
    int len = strlen(s);
    while( i < len && j < len && count < len) {
        t=s[(i + count)%len] - s[( j + count)%len] ;
        if( t==0) ++count;
        else {
            if(t > 0) i += count + 1 ;
            else j += count + 1 ;
            if( i == j ) j++ ;
            count = 0 ;
        }
    }
    int Size = 0 ;
    for( j = min(i,j) ; Size < len ; j ++ ,Size++)
        str[ Size ] = s[ j%len ] ;
    str[ Size ] = '\0' ;
}
