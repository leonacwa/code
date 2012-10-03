
/* C++ 的Algorithm 函数库
 * */
#include <algorithm>
/*
   InputIterator, iterator 都是迭代器，InputIterator明确表示这个参数是输入的参数

   ptrdiff_t是指针之间的差值，也就是之间之间元素个数差值，如 end() - begin() 的差值

*/

/* 
   循环处理函数
   一元函数Function，可以用一个函数或者类的()运算符实现，只有一个参数，无返回值
   N
 * */
Function for_each (InputIterator first, InputIterator last, Function f);
void f(T x) { // UnaryFunction
	// work
}

/*
   在无序序列中查找元素
   在[first, last) 找到第一个与value相等的元素并返回位置
   N
   */
InputIterator find ( InputIterator first, InputIterator last, const T& value );

/*
   在无序序列中查找满足条件pred的元素
   pred为一元函数，返回值为bool，true表示满足，false不满足
   N
   */
InputIterator find_if ( InputIterator first, InputIterator last, Predicate pred );
bool pred(T x) {  //Predicate 
	// test
}

/*
   在一个序列中查找两个相邻相等元素，并返回其中的第一个元素
   可以加入pred函数测试两个元素
   N-1
 * */
ForwardIterator adjacent_find ( ForwardIterator first, ForwardIterator last );
ForwardIterator adjacent_find ( ForwardIterator first, ForwardIterator last, BinaryPredicate pred );
bool pred( T a, T b ) { // BinaryPredicate
	// test
}

/*
   统计序列中有多少个值为val的元素
   ptrdiff_t是指针之间的差值，也就是之间之间元素个数差值，如 end() - begin() 的差值
   N
 * */
ptrdiff_t count ( InputIterator first, InputIterator last, const T& value );

/*
   统计序列中有多少个满足pred条件的元素
   N
 * */
ptrdiff_t count_if ( InputIterator first, InputIterator last, Predicate pred );
bool pred( T x ) {
	// test
}

/* 
   复制[first, last)的元素到以result开头的位置
   */
OutputIterator copy ( InputIterator first, InputIterator last, OutputIterator result );

/*
   复制[first, last)的元素到以result结尾的位置
   */
BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result );

/* 交换两个元素值
 * */
void swap ( T& a, T& b );

/*
   交换两个区间的元素
   将[first1, last1)的元素与以first2开头的区间交换
   返回[first2, last2)中的last2，即第二个序列的最后的位置 end
 * */
ForwardIterator2 swap_ranges ( ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2 );

/*
   交换两个迭代器指向的元素
   */
void iter_swap ( ForwardIterator1 a, ForwardIterator2 b );

/*
   第一个函数对[first1,last1)的元素都用一元函数op处理一遍并存到以result开头的结果区间，并返回结果区间的尾部
   第二个函数对[first1,last1)和[first2,last2)的元素都用二元元函数binary_op处理一遍，binary_op为两个参数并且一一对应
   即first1对first2, 并存到以result开头的结果区间，并返回结果区间的尾部
 * */
OutputIterator transform ( InputIterator first1, InputIterator last1,
		OutputIterator result, UnaryOperator op );

OutputIterator transform ( InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, OutputIterator result,
		BinaryOperator binary_op );

TYPE op(TYPE a) {
	//work
}
TYPE binary_op(TYPE a, TYPE b) {
	// work a b
}

/*
   将[first,last)中old_value替换为new_value
 * */
void replace ( ForwardIterator first, ForwardIterator last,
		const T& old_value, const T& new_value );

/*
   将[first,last)中满足pred条件测试的元素替换为new_value
 * */
void replace_if ( ForwardIterator first, ForwardIterator last,
		Predicate pred, const T& new_value );
bool pred (TYPE x) {
	// test x
}

/* 
   序列赋值函数，将[first,last)的元素都赋值为val
   */
void fill ( ForwardIterator first, ForwardIterator last, const T& value );
/*
   将[first,fisrt+n)的元素都赋值为val
   */
void fill_n ( OutputIterator first, Size n, const T& value );

/*
   将[first,last)区间的元素用gen函数赋值一遍，即生成一个值赋给这个区间的元素，每个元素调用一次gen函数
   */
void generate ( ForwardIterator first, ForwardIterator last, Generator gen );
/*
   将[first,first+n)区间的元素用gen函数赋值一遍
   */
void generate_n ( OutputIterator first, Size n, Generator gen );
TYPE gen() {
	// return generate data
}



/* 
   有序序列去重，返回新的end
   K*log(N)
 * */
ForwardIterator unique ( ForwardIterator first, ForwardIterator last );
ForwardIterator unique ( ForwardIterator first, ForwardIterator last,
		BinaryPredicate pred );

/*
   将[first,last)去重并放到以result开始的位置
   返回重复序列的end
   */
OutputIterator unique_copy ( InputIterator first, InputIterator last,
		OutputIterator result );
OutputIterator unique_copy ( InputIterator first, InputIterator last,
		OutputIterator result, BinaryPredicate pred );
/*
   翻转[fisrt,last)]序列，第二函数的result参数表示新的翻转序列存放开始位置
   返回翻转后目标序列的end
   */
void reverse ( BidirectionalIterator first, BidirectionalIterator last);
OutputIterator reverse_copy ( BidirectionalIterator first,
		BidirectionalIterator last, OutputIterator result );
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
OutputIterator merge ( 
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result );

OutputIterator merge ( 
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		OutputIterator result, Compare comp );

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

/* 生成下一个排列
 * 如果是ture表示成个生成下一个，false表示已经没有下一个，重新开始排列
 * */
bool next_permutation( iterator start, iterator end );
bool next_permutation( iterator start, iterator end, StrictWeakOrdering cmp );


