class TimeKeeper 														// base 클래스이다.
{
public:
	TimeKeeper();
	~TimeKeeper();														// 비가상 소멸자를 선언하였다.
	//virtual ~Timekeeper();											// 멤버 함수에 virtual 함수가 있다면
																		// 소멸자는 virtual로 선언해주어야 한다. 반드시!

	virtual getCurrentTime();											// 가상 함수를 선언하였다.
};

class AtomicClock:public TimeKeeper 									// TimeKeeper 클래스를 상속받은 derived 클래스이다.
{
	virtual getCurrentTime();											
};

TimeKeeper* getTimeKeeper();											// Timekeeper의 파생 클래스를 통해 동적으로 할당된 객체의 포인터 return

int main()
{
	TimeKeeper *ptk = getTimeKeeper();									// TimeKeeper의 파생객체(AtomicClock)로부터 동적으로 할당된 객체를 얻고


	delete ptk;															// 해제하였다.
																		// 하지만 TimeKeeper의 소멸자는 비가상 소멸자이기 때문에
																		// TimeKeeper의 소멸자가 호출될 때
																		// 파생 객체(AtomicClock)의 소멸자는 호출되지 않아
																		// 메모리 누수가 발생한다.
	return 0;
}