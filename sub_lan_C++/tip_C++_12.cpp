class Investment {...};										// base class, 많은 derived 객체에서 상속할 예정

Investment* createInvestment();								// 팩토리 함수, Investment의 derived 객체를 동적할당하고 base class인 
															// Investment의 포인터를 반환한다.
															// 이 함수를 호출한 caller가 동적할당된 객체를 해제시켜주어야 한다.

void f()
{
	std::shared_ptr<Investment> pinv1(createInvestment());	// delete로 직접 해제해 주는 것은 리스크가 매우 크다(중간에 return, 예외 발생 등)
															// createInvestment 함수를 부르는 동시에 객체(스마트포인터 등)로 초기화하는 기법(RAII)
															// 을 사용하여 f의 유효범위가 끝나는 순간 소멸자로 delete 되게 한다.
															// 한 스마트포인터 객체가 한 포인터만을 가리키게 하고 싶다면 unique_ptr
															// 중복 가리킴을 허용하고 복사 동작을 제대로 수행시키고 싶다면 shared_ptr을 사용한다.
}