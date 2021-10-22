// 비멤버 버전의 operator new 함수의 pseudo code
void* operator new(std::size_t size) throw(std::bad_alloc)		// 매개변수를 여러 개 가질 수도 있음
{
	if(size==0)													// 0바이트 할당 요청이 들어오면 1바이트로 처리
		size  1;

	while(true)													// 메모리 할당이 성공하던가, new handler가 제대로 처리해주지 않으면
	{															// 이 루프를 탈출하지 못한다.
		size바이트를 할당해 봅니다;
		if(할당이 성공했음)
			return (할당된 메모리에 대한 포인터);

		new_handler globalHandler = set_new_handler(0);			// 할당이 실패했을 경우, 현재의 new handler 함수가 어느 것으로
		set_new_handler(globalHandler);							// 설정되어 있는지 찾아낸다.

		if(globalHandler) (*globalHandler) ();					// new 처리자 함수에 대한 포인터가 널이면
		else throw std::bad_alloc();							// 예외를 던진다.
	}
}

// 비멤버 버전의 operator delete 함수의 pseudo code
void operator delete(void *rawMemory) throw()
{
	if(rawMemory == 0) return;									// null 포인터가 delete되려고 할 경우에는 아무것도 하지 않는다.

	rawMemory가 가리키는 메모리를 해제합니다;
}
