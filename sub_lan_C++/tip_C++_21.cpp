class WidgetImpl{};													// Widget의 실제 데이터를 나타내는 클래스
																	// 데이터가 많아 복사비용이 크다.
class Widget													
{																	 
public:
	Widget(const Widget& rhs);
	void swap(Widget& other)
	{
		using std::swap;
		swap(pImpl, other.pImpl);									// 포인터를 교환하는 방식으로 swap 구현
	}
private:
	WidgetImpl *pImpl;												// Widget의 실제 데이터를 가진 객체의 포인터
}

namespace std
{
	template<>
	void swap<Widget>(Widget& a, Widget& b)							// std::swap의 특수화 버전 
	{																	
		a.swap(b);
	}
}

// 표준 swap의 효율이 내가 정의한 클래스에 사용하긴 좀 별로일 때 swap 구현법
// 1. 본인 타입으로 된 두 객체를 교환하는 swap함수를 구현하고 public 멤버 함수로 둔다.
// 2. 내가 정의한 클래스와 같은 네임스페이스에 비멤버 swap을 만들고 멤버 함수 swap을 호출하도록 만든다.
// 3. 사용자는 using std::swap을 선언해두고 swap호출 시 네임스페이스 한정자를 붙이지 않는다.
// 멤버 swap 함수는 예외를 던지면 안된다!
