template<typename T> class Rational{};
template<typename T> const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {...}

int main()
{
	Rational<int> oneHalf(1,2);
	Rational<int> result = oneHalf * 2;					// 컴파일 에러

	return 0;
}

// 템플릿 인자 추론 과정에서는 암시적 타입 변환이 고려되지 않기 때문에 operator*는 2번째 매개변수의 타입을 추론할 수 없다.

// 위 문제를 해결하기 위한 첫번째 단계
// operator* 에게 T 타입을 알려주기 위해서 Rational 클래스 내에 public으로 friend 선언을 해준다.
template<typename T>
class Rational
{
public:
	friend const Rational operator*(const Rational& lhs, const Rational& rhs);
};

template<typename T>
const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {...}

// 컴파일 성공은 하지만 이번엔 링크 에러가 발생한다.
// 위 함수는 템플릿 내에서 선언만 되어 있지 정의는 찾을 수가 없다.

// 위 문제들을 해결하는 해결책
class Rational
{
public:
	friend const Rational operator*(const Rational& lhs, const Rational& rhs)
	{
		return Rational( lhs.numerator() * rhs.numerator(), ......... );
	}
};
// 모든 인자에 대해 타입 변환이 가능하도록 만들기 위해서는 비멤버 함수가 필요하고,
// 호출 시의 상황에 맞는 함수를 자동으로 인스턴스화하기 위해서는 그 비멤버 함수를 클래스 안에 선언해야 한다.
// 그리고 클래스 안에 비멤버 함수를 선언하는 유일한 방법이 friend 선언이었기 때문에 이런 이상한 형태가 나오게 되었다.

// 이런 방식은 결국 암시적 inline 선언이기 때문에 코드 비대화 문제가 생길 수 있다.

// 코드 비대화 문제를 해결하는 더 좋은 해결책
template<typename T> class Rational;

template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs);	// 도우미 함수 템플릿을 선언

template<typename T>
class Rational
{
	public:
	friend const Rational operator*(const Rational& lhs, const Rational& rhs)
	{ return doMultiply(lhs, rhs); }
};

template<typename T>
const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs)
{
	...		// 구현
}

// 실제 연산을 하는 함수는 헤더파일 외부에 정의해두고 이를 내부에서 호출하는 방식으로 코드 비대화를 해결할 수 있다.