class GameCharacter;

class HealthCalcFunc														// 이 클래스 계통에 파생클래스를 추가함으로써 다른 calc 함수를 적용할 수 있다.
{
public:
	...
	virtual int calc(const GameCharacter& gc) const
		{ ... }
	...
};

HealthCalcFunc defaultHealthCalc;

class Gamecharacter
{
public:
	explicit GameCharacter(HealthCalcFunc *phcf = &defaultHealthCalc)		// HealthCalcFunc 포인터를 인자로 받아 초기화하는 생성자
		: pHealthCalc(phcf) {}
	int healthValue() const
		{ return pHealthCalc->calc(*this); }								// 객체를 생성하고 이 함수를 호출하면 적용된 체력치 계산 함수에서 값을 구해온다.
	...
private:
	HealthCalcFunc *pHealthCalc;											// HealthCalcFunc 포인터를 데이터로 가지고 있다.
};