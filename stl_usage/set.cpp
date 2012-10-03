
#include <set>

/* 返回set的第一个元素
 * K
 * */
iterator begin();
const_iterator begin() const;

/* 返回set的最后一个元素的下一个位置，也就是end
 * K
 * */
iterator end();
const_iterator end() const;

/* 
 * 返回第一个大于等于key的元素
 * K*log(N)
 * */
iterator lower_bound( const key_type& key );

/* 
 * 返回第一个大于key的元素
 * K*log(N)
 * */
iterator upper_bound( const key_type& key );
