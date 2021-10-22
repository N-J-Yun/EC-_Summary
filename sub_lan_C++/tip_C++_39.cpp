// 특정 클래스(Widget)만을 위한 할당 에러 처리자 구현
class Widget
{
public:
	static std::new_handler set_new_handler(std::new_handler p) throw();	// 처리하고자 하는 클래스 내에서 set_new_handler와 
	static void* operator new(std::size_t size) throw(std::bad_alloc);		// operator new를 제공하도록 구현한다.
private:
	static std::new_handler currentHandler;									// Widget 객체를 담을 만큼의 메모리를 new가 할당하지 못했을 때
																			// 호출될 new 처리자 함수를 어딘가에 간수해 둘 필요가 있으므로
};																			// new_handler타입의 정적 멤버 데이터를 선언한다.

std::new_handler Widget::currentHandler = 0;								// 정적 클래스 멤버는 클래스 밖의 구현파일 내에 두고 null로 초기화

// 전역 new 처리자를 자원으로 삼아 Widget의 operator new를 구현한다.
// 자원 관리 클래스 구현
class NewHandlerHolder
{
public:
	explicit NewHandlerHolder(std::new_handler nh)							// 현재의 new 처리자를 받아 초기화한다.
		: handler(nh) {}

	~NewHandlerHolder()														// 받아온 new 처리자를 해제한다.
		{ std::set_new_handler(handler); }
	private:
		std::new_handler handler;											// new 처리자를 저장

		NewHandlerHolder(const NewHandlerHolder&);							// 복사 방지
		NewHandlerHolder& operator=(const NewHandlerHolder&);				// 복사 방지
};

// Widget::set_new_handler함수 구현
std::new_handler Widget::set_new_handler(std::new_handler p) throw()		
{
	std::new_handler oldHandler = currentHandler;							// std::set_new_handler의 역할과 똑같이
	currentHandler = p;														// 넘겨받은 포인터(지정할 처리자 함수)를 저장하고 
	return oldHandler;														// 이전에 저장했던 포인터(지정되었던 처리자 함수)를 반환한다.
}

// Widget::operator new 구현
void* Widget::operator new(std::size_t size) throw(std::bad_alloc)
{
	NewHandlerHolder h(std::set_new_handler(currentHandler));				// Widget의 new 처리자를 설치하고

	return ::operator new(size);											// 전역 operator new를 return 한다.

																			// 메모리를 할당할 수 있다면 할당된 메모리를 반환하고 소멸자 호출
																			// 소멸자가 호출되면 widget의 new가 호출되기 전에 쓰이던 전역 new
																			// 처리자가 자동으로 복원된다.

																			// 만약 전역 new가 할당을 실패하면 Widget의 new 처리자를 호출한다.
}

// 사용
void outOfMem();
int main()
{
	Widget::set_new_handler(outOfMem);				// Widget new handler를 셋팅하고
	Widget *pw1 = new Widget;						// new 할당이 실패하면 outOfMem이 호출된다.

	std::string *ps = new std::string;				// 전역 new handler가 복원되어 여기서 new 할당이 실패하면 전역 new handler 함수를 호출

	Widget::set_new_handler(0);						// 이번엔 Widget new handler를 null로 셋팅하고
	Widget *pw2 = new Widget;						// new 할당이 실패하면 이제는 예외를 바로 던진다.

	return 0;
}
