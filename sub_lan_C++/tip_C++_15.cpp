int priority();
void processWidget(std::shared_ptr<Widget> pw, int priority);

int main()
{
	processWidget(std::shared_ptr<Widget>(new Widget), priority());	// 언듯 보기엔 문제가 없지만, C++의 매개변수 평가 순서 때문에 문제 발생 가능
																	// C++의 매개변수 평가 순서는 컴파일러마다 다르다.
																	// 이 함수에 전달된 매개변수는 3 부분으로 나눌 수 있다.
																	// 1. new Widget / 2. shared_ptr 생성자 / 3. priority()
																	// 만약 1,3,2 순으로 호출된다고 할 때, priority()호출에서 예외가 발생한다면?
																	// new Widget으로 만들어졌던 포인터가 유실될 수 있다.-> 자원 누출

	std::shared_ptr<Widget> pw(new Widget);							// 해결책: new로 생성한 객체를 저장하는 스마트 포인터의 선언은 별도로 한다.

	processWidget(pw, priority());									

	return 0;
}