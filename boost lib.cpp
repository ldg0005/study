#define _CRT_SECURE_NO_WARNINGS

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <iostream>
using namespace std;
using namespace boost::multiprecision;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cpp_dec_float_100 f64Count = 10201.000000000000;
	cpp_dec_float_100 f64Covariance = 1896.0723956934758;
	cpp_dec_float_100 f64SumX = 2243098.0000000000;
	cpp_dec_float_100 f64SumY = 9576658.0000000000;
	cpp_dec_float_100 f64SumOfSquaresX = 520297128.00000000;
	cpp_dec_float_100 f64SumOfSquaresY = 1062542034.0000000;

	cpp_dec_float_100 f64Coeff = (f64Count * f64Covariance - (f64SumX * f64SumY)) / (sqrt((f64Count * f64SumOfSquaresX - f64SumX * f64SumX) * (f64Count * f64SumOfSquaresY - f64SumY * f64SumY)));

	cpp_dec_float_100 f64cov = ((f64Covariance * f64Count) - (f64SumX * f64SumY)) / (f64Count * f64Count);
	cpp_dec_float_100 f64sta1 = sqrt((f64SumOfSquaresX / f64Count) - ((f64SumX / f64Count) * (f64SumX / f64Count)));
	cpp_dec_float_100 f64sta2 = sqrt((f64SumOfSquaresY / f64Count) - ((f64SumY / f64Count) * (f64SumY / f64Count)));
	cpp_dec_float_100 f64coef = sqrt(((f64Count * f64SumOfSquaresX) - (f64SumX * f64SumX)) / (f64SumX * f64SumX));

	cpp_dec_float_100 result = f64coef;
	cpp_dec_float_100 result1 = f64cov / (f64sta1 * f64sta2);

	cout << fixed;
	cout.precision(20);
	cout << result << endl;


	return 0;
}

//boost 다운로드, 프로젝트 속성 C/C++, 일반, 추가 포함 디렉터리 
