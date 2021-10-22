// operator new 함수는 기본형과 달리 매개변수를 추가로 받는 형태로도 선언할 수 있다. 이런 형태의 함수를 위치지정 new라고 한다.

int main()
{
	Widget *pw = new (std::cerr) Widget;			// operator new를 먼저 호출하고 Widget의 생성자를 호출한다.
													// new를 부르고 Widget 생성자에서 예외가 발생하면 메모리가 누출된다.

													// 이럴 때 런타임 시스템이 자동으로 operator new와 짝이 맞는 delete를 호출해주는데
													// 짝이 맞는 delete가 정의 되어 있지 않다면 아무것도 하지않는다.
	return 0;
}

class Widget
{
public:
	static void* operator new(std::size_t size, std::ostream& logStream) throw(std::bad_alloc);
	static void operator delete(void* pMemory) throw();
	static void operator delete(void* pMemory, stsd::ostream& logStream) throw();		
													// 짝이 맞는 위치지정 new/delete를 선언해 주었다.
};

int main()
{
	Widget *pw = new (std::cerr) Widget;			// 하지만 예외가 발생하지 않는다면?

	delete pw;										// 기본형 delete를 호출하기 때문에 위처럼 기본형 delete도 선언해주어야한다.

	return 0;
}

// 그리고 만약 위치지정 new를 사용자 정의하여 사용하려 한다면 기본적으로 C++가 전역 유효범위에서 제공하는 3가지 operator new를 가리지 않게 해야한다.
// new/delete의 기본형태를 전부 넣어두고 상속하여 사용한다.
class StandardNewDeleteForms
{
public:
	// 기본형 new/delete
	static void* operator new(std::size_t size) throw(std::bad_alloc)
		{ return ::operator new(size); }
	static void operator delete(void *pMemory) throw()
		{ return ::operator delete(pMemory); }
	// 위치지정 new/delete
	static void* operator new(std::size_t size, void *ptr) throw(std::bad_alloc)
		{ return ::operator new(size, ptr); }
	static void operator delete(void *pMemory, void *ptr) throw()
		{ return ::operator delete(pMemory, ptr); }
	// 예외불가 new/delete
	static void* operator new(std::size_t size, const std::nothrow_t& nt) throw(std::bad_alloc)
		{ return ::operator new(size, nt); }
	static void operator delete(void *pMemory, const std::nothrow_t& nt) throw()
		{ return ::operator delete(pMemory); }
};

class Widget: public StandardNewDeleteForms
{
public:
	using StandardNewDeleteForms::operator new;
	using StandardNewDeleteForms::operator delete;

	...												// 사용자 정의 위치지정 new/delete를 추가한다.
};