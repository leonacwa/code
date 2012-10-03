/* C++中使用cstdlib，C中使用stdlib.h
 * */

#include <cstdlib>

/* 折半查找法在 buf[0] .. buf[num-1] 中查找key，
 * compare中第一个参数小于第二个参数则返回负值，等于返回0，否则返回正值
 * 找到则返回匹配项的指针，否则返回NULL
 * */
void *bsearch( const void *key, const void *buf, size_t num, size_t size, int (*compare)(const void *, const void *) );


