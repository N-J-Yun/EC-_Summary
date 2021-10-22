// 파생 클래스들이 한 가지의 특정 기능만을 물려받아 갈 수 있도록 설계된 base 클래스 구현
// 클래스별 set_new_handler를 지원하는 믹스인 양식의 기본 클래스(tip_C++_39 참고)
template<typename T>
class NewHandlerSupport
{
public:
	static std::new_handler set_new_handler(std:;new_handler p) throw();
	static void* operator new(std::size_t size) throw(std::bad_alloc);
	...
private:
	static std::new_handler currentHandler;
};

template<typename T>
std::new_handler
NewHandlerSupport<T>::set_new_handler(std::new_handler p) throw()
{
	std::new_handler oldHandler = currentHandler;
	currentHandler = p;
	return oldHandler;
}

template<typename T>
void*
NewHandlerSupport<T>::operator new(std::size_t size) throw(std::bad_alloc)
{
	NewHandlerHolder h(std::set_new_handler(currentHandler));
	return ::operator new(size);
}

template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;
// base 클래스는 파생 클래스들이 가져야 하는 set_new_handler 함수와 operator new 함수를 물려준다.
// 템플릿 부분은 각 파생 클래스가 인스턴스화된 클래스가 되면서 currentHandler 데이터 멤버를 따로따로 가질 수 있게 한다.

// 상속 예시
class Widget: public NewHandlerSupport<Widget>			// 쓰지도 않는 타입 T에 Widget을 넣어 상속받는 이 모습이 이상해 보일 수도 있지만
														// 특이한 기법 중 하나이다. "넌 나만의 템플릿이야"" 라는 의미로 이해하자. 
{
	// 이전과 같지만, 이제는 set_new_handler 혹은 operator new에 대한 선언문이 빠져있다.
}

// NewHandlerSupport 템플릿 클래스는 사실 T를 사용하지 않는다!
// 이 T는 그저 NewHandlerSupport<Widget> 처럼 파생 클래스들을 구분해 주는 역할만 할 뿐이다.

// 믹스인 양식을 쓰기 위해서는 다중상속을 걱정하게 되는데 이는 최대한 고민한 후에 효율적이라는 판단이 든다면 사용하도록 하자.