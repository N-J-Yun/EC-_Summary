class Transaction
{
public:
	Transaction();
	virtual void logTransaction() const = 0;
};

Transaction::Transaction()
{
	logTransaction();														// 생성자 내에서 가상함수를 호출하였다.
																			// 에러가 발생한다.(소멸자도 마찬가지)
}

// // 더럽고 사악한 경우
// Transaction::Transaction()
// {
// 	Init();																	// Init 함수 내에서 가상함수를 호출했다면???
// 																			// 컴파일 에러가 알아차리지 못하고 정상적으로 실행한다.
// 																			// 어리둥절 하면서 뭐가 문젠지 하루종일 찾을 게 분명하다.
// }

class BuyTransaction: public Transaction
{
public:
	virtual void logTransaction() const;
};

int main()
{
	BuyTransaction b;														// BuyTransaction 생성자가 호출되기 전에 Transaction 생성자가 호출된다.
																			// 하지만 파생 클래스 객체(BuyTransaction)의 base 클래스(Transaction)
																			// 부분이 생성되는 동안은 그 객체의 타입은 base 클래스이다!
																			// (의도한대로 진행되도 문제이다. 파생 클래스 객체의 데이터 부분은
																			// 초기화가 되지 않았을 것이 분명하기 때문이다.)
																			// 따라서 원래라면 logTransaction은 base 클래스(Transaction)의
																			// logTransaction을 호출할 것이다.
																			// 하지만 컴파일러가 생성자,소멸자 내에 사용된 가상 함수를 발견하고
																			// 에러를 띄워 줄 것이다.

	return 0;
}