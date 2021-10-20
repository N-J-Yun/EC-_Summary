template<typename C>
void print2nd(const C& container)
{
	if(container.size() >= 2)
	{
		C::const_iterator iter(container.begin());				// C::const_iterator는 템플릿 매개변수에 종속되어 있기 때문에 중첩의존이름이라 부른다.
																// 컴파일러의 구문 분석기는 중첩 의존 이름을 기본적으로 타입이 아닌 것으로 해석한다.
																// 타입이 아니라 C의 정적 데이터 멤버인 const_iterator라고 생각할 수도 있다.

		typename C::const_iterator iter(container.begin());		// 이제 문제 해결, 타입이라고 컴파일러에게 알려주었다.
		++iter;
		int value = *iter;
		std::cout << value;
	}
}

// 중첩 의존 이름에 typename을 붙이면 안되는 예외
template<typename T>
class Derived: public Base<T>::Nested							// 상속되는 base 클래스 리스트에 중첩 의존 이름이 올 경우
{
public:
	explicit Derived(int x)
		: Base<T>::Nested(x)									// 멤버 초기화 리스트에 있는 base 클래스 식별자에 중첩 의존 이름이 올 경우
		{
			typename Base<T>::Nested temp;						// 그 외에는 typename 붙여줘야 함.
			...
		}
	...
};

// template<typename T> 와 template<class T>는 같은 의미이다.