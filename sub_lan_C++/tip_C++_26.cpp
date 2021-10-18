class PrettyMenu
{
public:
	void changeBackground(std::istream& imgSrc);
private:
	Mutex mutex;
	Image*bgImage;
	int imageChanges;
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
	lock(&mutex);

	delete bgImage;
	++imageChanges;													// 아래에서 예외가 터지면 change를 하지도 못했는데 회수만 증가하게 된다.
	bgImage = new Image(imgSrc);									// 여기서 예외가 터진다면?
																	// mutex에 갇힌다. 그리고 이미지도 삭제된 채로 이전 상태로 돌아가지 못한다.

	unlock(&mutex);
}

// 좋은 구현(강력한 보장에 거의 가까워진 기본적인 보장 제공)
class PrettyMenu
{
	std::shared_ptr<Image> bgImage;									// shared_ptr로 자원을 관리하면 해제에 대한 걱정을 덜 수 있다.
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
	Lock m1(&mutex);												// 임계영역을 벗어나면 자동으로 unlock(tip_C++_13 참조)
	bgImage.reset(new Image(imgSrc));								// new Image(imgSrc)가 제대로 생성되지 않으면 delete도 수행되지 않는다.
																	// 따라서 예외가 발생한다고 해도 이전 상태로 돌아갈 수 있다.
	++imageChanges;													// reset이 수행되었다면 change 횟수를 올려준다.
}

// 예외 안전성을 가진 함수라면
// 1. 자원이 새도록 만들지 않는다. -> 자원 관리 객체를 만들어 해결(tip_C++_12 참조)
// 2. 자료구조가 더럽혀지는 것을 허용하지 않는다.

// 세 가지 guarantee 중 하나를 제공해야 한다.
// 1. 예외불가 보장: 예외를 절대로 던지지 않겠다는 보장, 약속한 동작은 끝까지 완수한다는 의미이다.
// 	기본제공 타입에 대한 연산은 예외를 던지지 않는다. 
//  하지만 구현하기 매우 어렵고 사실상 불가능하다.
// 2. 강력한 보장: 함수 동작 중에 예외가 발생하면, 프로그램의 상태를 절대로 변경하지 않겠다는 의미이다.
// 호출이 성공하면 마무리까지 완벽하게 성공하고, 호출이 실패하면 함수 호출이 없었던 것처럼 프로그램의 상태가 되돌아간다.
// 하지만 이를 보장하기 위해서는 실용성을 포기해야할 수도 있다. 실용성이 확보된다면 반드시 제공하자.(copy & swap을 통해 구현할 수 있지만 실용성은 제공 X)
// 3. 기본적인 보장: 함수 동작 중에 예외가 발생하면, 실행 중인 프로그램에 관련된 모든 것들을 유효한 상태로 유지하겠다는 의미이다.
// 실용성이 확보되었을 때 강력한 보장을 제공하였다면, 그 외의 부분에 대해서는 기본적인 보장을 제공해도 문제 없다.
// 
