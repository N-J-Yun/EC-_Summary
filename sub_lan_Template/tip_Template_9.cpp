class Top { ... };
class Middle :public Top{ ... };
class Bottom :public Middle{ ... };

template<typename T>
class SmartPtr
{
public:
	explicit SmartPtr(T *realPtr);
};

int main()
{
	SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);
	SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Middle);
	SmartPtr<const Top> pct1 = pt1;										// 기본 포인터에서는 가능한 연산들이지만 스마트 포인터를 통해서는 불가능하다.

	return 0;
}

// 위와 같은 문제를 생성자 역할을 하는 멤버 함수 템플릿으로 해결할 수 있다.
template<typename T>
class SmartPtr
{
public:
	template<typename U>
	SmartPtr(const SmartPtr<U>& other)								// 일반화 복사 생성자(같은 템플릿을 써서 인스턴스화되지만 타입이 다른
																	// 타입의 객체로부터 원하는 객체를 만들어 주는 생성자)
																	// smartPtr<T> 객체가 SmartPtr<U>로부터 생성될 수 있다

		: heldPtr(other.get()) { ... }								// SmartPtr<T>의 데이터 멤버이 T*포인터를 SmartPtr<U>에 들어있는 U*포인터로 초기화했다.
																	// -> U*에서 T*로 진행되는 암시적 변환이 가능할 때만 컴파일 에러가 나지 않는다.
	T* get() const { return heldPtr; }
private:
	T *heldPtr;
};
// SmartPtr<T>의 일반화 복사 생성자는 호환되는 타입의 매개변수를 넘겨받을 때만 컴파일 되도록 만들어졌다.

// 호환되는 모든 타입을 받아들이는 멤버 함수를 만들려면 멤버 함수 템플릿을 사용하자.
// 일반화된 복사 생성 연산과 일반화된 대입 연산을 위해 멤버 템플릿을 선언했다 하더라도, 보통의 복사 생성자와 복사 대입 연산자는 여전히 직접 선언해야한다.