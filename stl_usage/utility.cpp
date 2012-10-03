/*
   utility库

 * */
#include <utility>
using namespace std;

/*
   pair类型模板，支持含有两个元素的对象，如一个平面坐标(x,y)
   first是第一个元素，second是第二个元素
   */
template <class T1, class T2> struct pair;
// pair的实现
template <class T1, class T2> struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;
	pair() : first(T1()), second(T2()) {}
	pair(const T1& x, const T2& y) : first(x), second(y) {}
	template <class U, class V>
		pair (const pair<U,V> &p) : first(p.first), second(p.second) { }
}

/*
   返回一个pair<T1,T2>的元素,first为x,second为y
   */
template <class T1, class T2> pair<T1,T2> make_pair (T1 x, T2 y);
// make_pair 实现
template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}

/*
   rel_ops名字空间，可以让某种类型的元素支持命名空间的操作
   需要额外声明using namespace rel_ops;
   */
namespace rel_ops {
	template <class T> bool operator!= (const T& x, const T& y) { return !(x==y); }
	template <class T> bool operator>  (const T& x, const T& y) { return y<x; }
	template <class T> bool operator<= (const T& x, const T& y) { return !(y<x); }
	template <class T> bool operator>= (const T& x, const T& y) { return !(x<y); }
}
