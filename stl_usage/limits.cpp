/*
   cpp的limits库，初始包含基本类型的信息，如int,char,double等
 * */
// 未完成
#include <limits>
using namespace std;

/*
  numeric_limits限制对象，如果需要int的信息，专门化类型numeric_limits<int>即可
  limits已经专门化了:
  bool, char, signed char, unsigned char, wchar_t, short, unsigned short, int, unsigned int, long, unsigned long, float, double, long double
  的基本类型数据，直接使用即可
   */
template <class T> class numeric_limits {
	public:
		static const bool is_specialized = false;
		static T min() throw();
		static T max() throw();
		static const int  digits = 0;
		static const int  digits10 = 0;
		static const bool is_signed = false;
		static const bool is_integer = false;
		static const bool is_exact = false;
		static const int radix = 0;
		static T epsilon() throw();
		static T round_error() throw();

		static const int  min_exponent = 0;
		static const int  min_exponent10 = 0;
		static const int  max_exponent = 0;
		static const int  max_exponent10 = 0;

		static const bool has_infinity = false;
		static const bool has_quiet_NaN = false;
		static const bool has_signaling_NaN = false;
		static const float_denorm_style has_denorm = denorm_absent;
		static const bool has_denorm_loss = false;
		static T infinity() throw();
		static T quiet_NaN() throw();
		static T signaling_NaN() throw();
		static T denorm_min() throw();

		static const bool is_iec559 = false;
		static const bool is_bounded = false;
		static const bool is_modulo = false;

		static const bool traps = false;
		static const bool tinyness_before = false;
		static const float_round_style round_style = round_toward_zero;
}


