class GameCharacter;													// 전방 선언

int defaultHealthCalc(const GameCharacter & gc);						// 체력치 계산에 대한 기본 알고리즘을 구현한 함수

class GameCharacter
{
public:
	typedef int (*HealthCalcFunc) (const GameCharacter&);				

	explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc)		// 체력치 계산 함수를 인자로 받는 생성자
		: healthFunc(hcf) {}
	int healthValue() const												// *this를 체력치 계산 함수에 넘겨 return 한 값을 return 한다.
		{ return healthFunc(*this); }
	...
private:
	HealthCalcFunc healthFunc;
};

class EvilBadGuy: public GameCharacter									// 파생 클래스
{
public:
	explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc)
		: GameCharacter(hcf)
		{ ... }
	...
};

int loseHealthQuickly(const GameCharacter&);							// GameCharacter를 인자로 받는 체력치 계산 함수
int loseHealthSlowly(const GameCharacter&);

int main()
{
	EvilBadGuy evg1(loseHealthQuickly);									// 같은 타입의 캐릭터 임에도 체력치 계산 알고리즘이 다르다.
	EvilBadGuy evg2(loseHealthSlowly);
	return 0;
}

// Strategy 패턴의 단순 응용 버전
// 이점 1. 같은 캐릭터 타입으로부터 만들어진 객체들도 서로 다른 체력치 계산 함수를 가질 수 있다.
// 이점 2. 게임이 실행되는 도중에 특정 캐릭터에 대한 체력치 계산 함수를 바꿀 수 있다.

// 하지만 각각 구현한 체력치 계산 함수는 GameCharacter의 private 멤버에 접근할 수 있는 방법이 없다.
// friend, getter 등의 방법이 있지만 그 클래스의 캡슐화를 약화시키는 방법이다.
// 이점이 불이익보다 큰 지는 알아서 판단하자.