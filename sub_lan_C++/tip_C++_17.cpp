Investment* createInvestment();									// 인터페이스 사용자는 이 함수 호출을 통해 얻은 포인터를 직접 해제해야한다.
																// 하지만 사용자는 이를 잊어버릴 수도 있고, delete를 두 번 이상 적용할 수도 있다.

std::shared_ptr<Investment> createInvestment();					// shared_ptr에 포인터를 감싸서 위 문제를 해결하고
																// 감싼 shared_ptr 타입으로 반환하여 사용자가 shared_ptr을 사용해야한다는 사실을	
																// 잊을 가능성도 사전에 차단한다.

std::shared_ptr<Investment> createInvestment()					// 아래의 캐스팅 방식을 이용해 사용자에게 자원 관리 작업을 떠넘기지 않는
{																// 팩토리 함수를 구현하였다.
	std::shared_ptr<Investment> 
		retVal(static_cast<Investment*>(0)
			,getRidOfInvestment);
	retVal = ...;
	return retVal;
}

int main()
{
	std::shared_ptr<Investment> 								// getRidOfInvestment를 deleter로 지정하고 싶었지만 첫 번째 인자때문에 에러 발생
		pInv1(0, getRidOfInvestment);							// 0은 포인터가 아니라 int이다. 타입이 맞지 않다.(그 의도는 null이 었을지라도)


	std::shared_ptr<Investment> 	
		pInv1(static_cast<Investment*>(0)						// 0을 캐스팅을 통해 Investment* 타입 널 포인터로 바꿔주었다.
			, getRidOfInvestment); 

	return 0;
}