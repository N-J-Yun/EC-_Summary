namespace std
{
	typedef void (*new_handler) ();							// 매개변수가 없고 void를 반환하는 함수포인터에 typedef를 걸어놓은 것

	new_handler set_new_handler(new_handler p) throw();		// set_new_handler는 미리 지정된 handler p를 반환한다.
															// (new가 요구된 메모리를 할당하지 못했을 경우) 

															// throw()는 여기서 예외가 절대로 발생하지 않는다는 의미이지만,
															// 이는 실제로 예외가 발생하지 않도록 방지하겠다는 의미는 아니다. 그저 알려줄 뿐이다.
															// 여기서 예외가 발생하면 매우 심각한 상황이며, 실제로는 unexpected 함수를 호출한다.

}

void outOfMem()
{
	std:: cerr << "Unable to satisfy request for memory\n";
	std::abort();
}

int main()
{
	std::set_new_handler(outOfMem);
	int *pBigDataArray = new int[10000000000000000000L];	// new가 충분한 메모리를 할당못했으면 outOfMem을 호출한다.

	return 0;
}

// 좋은 new handler 함수가 하나는 해야하는 동작들
// 1. 사용할 수 있는 메모리를 더 많이 확보한다.
// 2. 다른 new 처리자를 설치한다.(처리자 내에서 set_new_handler를 호출한다.)
// 3. new 처리자의 설치를 제거한다.(set_new_handler에 널 포인터를 넘긴다.)
// 4. 예외를 던진다.(bad_alloc 에서 파생된 타입의 예외)
// 5. 복귀하지 않는다(abort, exit)