class GameCharacter
{
public:
	int healthValue() const										// 비가상 함수이기 때문에 파생 클래스는 이 함수를 재정의 할 수 없다.
	{
		...														// 사전 동작 수행
		int retval = doHealthValue();							// 실제 동작 수행(private 가상 함수를 호출하는 방식)
		...														// 사후 동작 수행
		return retVal;
	}
private:
	virtual int doHealthValue() const							// 실제 동작을 수행하는 가상 함수
	{															// 파생 클래스마다 이 함수를 구현하여야 한다.
		...
	}
};
// NVI 관용구(non-virtual interface)
// 위의 비가상 함수를 가상 함수의 래퍼라고 부른다.
// NVI 관용구는 사전, 사후 동작이 실제 동작 수행과 구분되어 실행될 수 있다는 큰 이점이 있다.