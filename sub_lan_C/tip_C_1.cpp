#include<iostream> 

#define ASPECT 1.653

int main()
{
	ASPECT = 5; 		// error, 상수에 값을 대입할 수 없다.
						// 컴파일러가 처리하기 전에 전처리기에서 ASPECT를 1.653으로 바꿔버려서 컴파일러는 ASPECT라는 이름을 모른다.
						// 컴파일러의 symbol table에 ASPECT라는 이름이 없기 때문에 디버깅할 때 어디서 에러가 났는지 찾기 힘들 수 있다.
						// 다른 사람이 ASPECT를 정의했다면 특히 원인 및 에러 위치를 찾기 어렵다.

	const int a = 3;	// + 매크로로 정의했을 경우 1.653의 사본이 등장횟수 만큼 obj 코드 안에 들어가지만,
						// const로 정의한 경우 사본은 딱 1개만 생긴다!

	a = 5;				// error, 컴파일러는 a라는 상수의 이름을 알고 사용자에게 알려준다. (symbol table에 저장되어 있음.)


	return 0;
}