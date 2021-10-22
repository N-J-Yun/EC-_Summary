// 사용자 정의 operator new,delete 클래스 전용 버전
// 자신이 할당하기로 예쩡된 크기보다 더 큰(틀린) 메모리 블록에 대한 요구도 처리해야 한다.
class Base
{
public:
	static void* operator new(std::size_t size) throw(std::bad_alloc);
	static void operator delete(void *rawMemory, std::size_t size) throw();
	...
};

void* Base::operator new(std::size_t size) throw(std::bad_alloc)
{
	if(size != sizeof(Base))						// 틀린 크기가 들어오면
		return ::operator new(size);				// 표준 operator new 쪽에서 메모리 할당 요구를 처리하도록 넘긴다.

	...												// 맞는 크기가 들어오면 메모리 할당 요구를 여기서 처리한다.
}

void Base::operator delete(void *rawMemory, std::size_t size) throw()
{
	if(rawMemory == 0) return;						// 널 포인터에 대한 점검

	if(size != sizeof(Base))						// 크기가 틀린 경우
	{
		::operator delete(rawMemory);				// 표준 operator delete가 메모리 삭제 요청을 맡도록 한다.
		return;
	}

	rawMemory가 가리키는 메모리를 해제합니다;

	return;
}

class Derived: public Base {...};					// Derived에서는 operator new가 선언되지 않았다.

int main()
{
	Derived *p = new Derived;						// 위의 틀린 크기 검사 코드가 없다면 Base::operator new가 호출된다!

	return 0;
}

