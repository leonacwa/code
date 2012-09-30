#include <algorithm>

/* 复制
 * */
iterator copy( iterator start, iterator end, iterator dest );

/* 序列统一复制函数
 * */
void fill( iterator start, iterator end, const TYPE& val );

/* 生成下一个排列
 * 如果是ture表示成个生成下一个，false表示已经没有下一个，重新开始排列
 * */
bool next_permutation( iterator start, iterator end );
bool next_permutation( iterator start, iterator end, StrictWeakOrdering cmp );

/* 翻转函数
 * */
 void reverse( iterator start, iterator end );

 /* 交换两个元素值
  * */
 void swap( Assignable& a, Assignable& b );

/******************************   有序相关    ******************************************************/
/* 有序序列去重，返回新的end
 * K*log(N)
 * */
iterator unique( iterator start, iterator end );
iterator unique( iterator start, iterator end, BinPred p );

/*
 * 在有序序列里查找第一个能插入的位置
 * 返回val能插入的位置
 * 如序列 0 1 2 3，插入-1，则会返回0的位置it，用vector的insert(it, -1),序列为-1 0 1 2 3
 * 插入0，则会返回0的位置it，形成序列 : 0(新) 0 1 2 3
 * K*log(N)
 * */
iterator lower_bound( iterator first, iterator last,  const TYPE& val );
iterator lower_bound( iterator first, iterator last, const TYPE& val, CompFn f );

/*
 * 在有序序列里查找最后一个能插入的位置
 * K*log(N)
 * */
iterator upper_bound( iterator start, iterator end, const TYPE& val );
iterator upper_bound( iterator start, iterator end, const TYPE& val, StrictWeakOrdering cmp );

/* 归并函数
 * K*N
 * */
iterator merge( iterator start1, iterator end1, iterator start2, iterator end2, iterator result );
iterator merge( iterator start1, iterator end1, iterator start2, iterator end2, iterator result, StrictWeakOrdering cmp );

/**    堆排序  ********************/
/* 建堆
 * K*N
 * */
void make_heap( iterator start, iterator end );
void make_heap( iterator start, iterator end, StrictWeakOrdering cmp );

/* 取出最大元素，即堆顶元素
 * K*log(N)
 * */
void pop_heap( iterator start, iterator end );
void pop_heap( iterator start, iterator end, StrictWeakOrdering cmp );

/* 将一个元素压入堆
 * K*log(N)
 * */
void push_heap( iterator start, iterator end );
void push_heap( iterator start, iterator end, StrictWeakOrdering cmp );

/* 检测是否是堆
 * K*N
 * */
bool is_heap( iterator start, iterator end );
bool is_heap( iterator start, iterator end, StrictWeakOrdering cmp );

/* 堆排序: 没有用过
 * */
void sort_heap( iterator start, iterator end );
void sort_heap( iterator start, iterator end, StrictWeakOrdering cmp );

