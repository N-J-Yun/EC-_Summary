class Lock 														// 뮤텍스 잠금을 관리하는 클래스
{
public:
	explicit Lock(Mutex *pm)
		: mutexPtr(pm)
		{ lock(mutexPtr); }
	~lock() { unlock(mutexPtr); }								// 소멸자를 통해 자동으로 unlock
private:
	Mutex *mutexPtr;
};

// RAII 객체에 복사를 시도할 때 이루어질 동작 유형
// 1. 복사 금지
// 항목 6, tip_C++_6 참조
class Lock: private Uncopyable {
};

// 2. 관리하고 있는 자원에 대해 참조 카운팅을 수행
// shared_ptr의 복사 방식과 동일하기 때문에 shared_ptr을 사용한다.
// 하지만 shared_ptr은 카운트가 0이 되면 자동으로 객체를 삭제시키기 때문에
// 생성자에 deleter를 지정해 주어(unlock) 구현한다.
class Lock
{
public:
	explicit Lock(Mutex *pm)
		: mutexPtr(pm, unlock)
		{ lock(mutexPtr.get()); }
	// 여기 소멸자가 없는 것을 확인할 수 있는데, 이럴 땐 주석을 통해 자동으로 소멸자를 불러줌을 알려주는 것이 좋다.
private:
	std::shared_ptr<Mutex> mutexPtr;
};

// 3. 관리하고 있는 자원을 진짜로 복사한다.
// 자원 관리 객체를 복사할 때 그 안의 자원까지 복사하여(deep copy) 
// 자원을 다 썼을 때 각각의 사본을 확실히 해제해 주어야 한다.

// 4. 관리하고 있는 자원의 소유권을 옮긴다.
// unique_ptr의 복사 방식과 동일하다.

int main()
{	
	Mutex m;
	{
		Lock m1(&m);											// 임계영역을 나가면 자동으로 unlock 된다.

		Lock m12(m1);											// 하지만 RAII객체에 복사를 시도한다면?
	}

	return 0;
}