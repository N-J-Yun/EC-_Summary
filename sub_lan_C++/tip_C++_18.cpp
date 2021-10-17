class Rational
{
public:
	Rational(int numerator = 0, int denominator = 1);
	...
private:
	int n,d;
	friend
	const Rational operator*(const Rational& lhs, const Rational& rhs);			// 실수 곱 연산자 오버로딩
}

inline const Rational operator*(const Rational& lhs, const Rational& rhs)		// 지역객체를 참조반환할 수는 없기 때문에 pass by value로 반환
{
	return Rational(lhs.n * rhs.n, lhs.d * rhs.d);								// 새로운 객체를 반환해야 하는 함수를 작성하는 법
																				// 컴파일러의 RVO(반환 값 최적화) 덕분에 생각한 것보다 
																				// 효율적으로(빠르게) 의도대로 동작할 것이다.
}