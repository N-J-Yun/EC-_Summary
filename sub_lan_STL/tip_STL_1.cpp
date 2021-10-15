#include<string>
class SpecialString: public std::string{						// STL 컨테이너 타입 전부가 비가상 소멸자를 가지고 있다.
																// 따라서 SpecialString 객체 포인터를 생성하고 delete한다면?
																// 메모리 누수가 발생할 수밖에 없다.
};

																// STL 컨테이너 타입을 상속받아서 사용자 정의 클래스를 만드려고 했다면
																// 포기해라!
int main()
{
	SpecialString *pss = new SpecialString();
	std::string *ps;

	ps = pss;													// SpecialString* => std::string*

	delete ps;													// undefined behavior!
																// SpecialString의 소멸자가 호출되지 않아 메모리 누수 발생!
}