class GameCharacter;													

int defaultHealthCalc(const GameCharacter & gc);						

class GameCharacter
{
public:
	typedef std::function<int (const GameCharacter&)> HealthCalcFunc;				// HealthCalcFunc는 함수 호출성 객체를 담을 수 있다.

	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)		
		: healthFunc(hcf) {}
	int healthValue() const												
		{ return healthFunc(*this); }
	...
private:
	HealthCalcFunc healthFunc;
};

short calcHealth(const GameCharacter&);												// HealthCalcFunc과 타입이 호환되는 체력 계산 함수

struct HealthCalculator
{
	int operator() (const GameCharacter&) const										// 체력치 계산용 함수 객체
	{ ... }
};

class GameLevel
{
public:
	float health(const GameCharacter&) const;										// 체력치 계산에 쓰일 멤버 함수
	...
};

class EvilBadGuy: public GameCharacter									
{
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter(hcf)
		{ ... }
	...
};

class EyeCandyCharacter: public GameCharacter
{
	...
};

int main()
{
	EvilBadGuy ebg1(calcHealth);													// 체력치 계산 함수 사용

	EyeCandyCharacter ecc1(HealthCalculator());										// 체력치 계산 함수 객체 사용

	GameLevel currentLevel;															
	...
	EvilBadGuy ebg2(
		std::bind(&GameLevel::health, currentLevel									// GameLevel::health는 사실 인자를 2개 받는다.
			, _1));																	// GameLevel 객체와 GameCharacter를 받기 때문에
																					// 생성자로 넘겨주기 위해서는 인자를 GameCharacter만 받는
																					// 형태로 만들어 주어야 한다.
																					// bind를 통해 GameLevel::health가 호출하는 GameLevel 객체는
																					// currentLevel로 고정시켰다.

																		// 이런 방식을 통해 체력치를 재설정 해주는 함수가 구현되어 있다면
																		// 게임 레벨에 맞는 캐릭터의 체력치를 설정해줄 수 있다.
	return 0;																		
}

// functional 헤더의 function 을 사용함으로써, 사용자가 게임 캐릭터의 체력치를 계산할 때 시그니처가 호환되는 함수 호출성 개체는 어떤 것도
// 원하는 대로 구사할 수 있도록 융통성을 활짝 열어주었다.
