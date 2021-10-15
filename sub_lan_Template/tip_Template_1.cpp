#include <iostream>
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))		// ++d라는 식 자체를 a로 받아와서 b와 값을 비교한 뒤 
															// 더 큰 값인 a 를 f에게 넘겨주는 매크로 함수
															// 첫 번째 호출에서 ++d가 한 번 더 실행되어 d는 7이 된다.

															// ++d를 a로 받지만 두 번째 호출 때는 b가 값이 더 크기 때문에
															// ++이 두 번 되지는 않는다.(d는 8)


template<typename T>									
inline void callWithMax(const T& a, const T& b)			// 타입 T에 대한 템플릿 함수이다.(위 매크로와 같은 역할을 한다.)
{														// 전역범위에 inline되었고, 진짜 함수이기 때문에 유효범위 및 접근 규칙을 그대로 따라간다.
	f(a > b ? a : b);									// 위의 매크로를 쓰지 말고 이런 형식을 쓰도록 하자! 
}														

void f(int asdf){}

int main()
{
	int d=5, b=0;

	CALL_WITH_MAX(++d, b);									

	std::cout << d << b << "\n"; 	// 7 0

	CALL_WITH_MAX(++d, b + 10);

	std::cout << d << b; 			// 8 0

	return 0;
}