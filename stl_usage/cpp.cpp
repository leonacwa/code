/* C++仿函数
 * 重载结构体或者类()运算符来充当一个函数的功能
 * */

// myclass是对象函数,重载了()运算符
struct myclass {
	  int operator()(int a) {return a;}
} myobject;
int x = myobject (0);           // function-like syntax with object myobject

template <class T>
struct Compare {
	bool operator() (const T &a, const T &b) const {
		return a < b;
	}
};

template <class T>
class Compare {
	public:
		bool operator() (const T &a, const T &b) const {
			return a < b;
		}
};

