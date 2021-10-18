class Person
{
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	...
private:
	std::string theName;
	Date theBirthDate;										// 구현 세부사항에 속하는(Date, Address, string)의 정의를 가져와야 컴파일 가능
	Address theAddress;										// -> <string> "date.h" "address.h" 헤더 파일을 include해야 컴파일이 됨.
															// 이런 구조로 설계하면 파일 사이의 컴파일 의존성이 생겨버리기 때문에
															// 위 헤더파일에서 수정 사항이 생기면 엮여있는 소스파일 모두를 재컴파일 해야한다.
};

//위 문제를 해결할 설계 방법 (pimpl)
#include<string>											// 표준 라이브러리의 include는 엥간해선 컴파일 병목현상의 원인이 되지는 않는다.
#include<memory>

class PersonImpl;											// Person의 구현 클래스에 대한 전방 선언
class Date;													// Person 클래스 안에서 사용하는 것들에 대한 전방 선언
class Address;

class Person
{
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name() const;
	std::string birthDate() const;
	std::string address() const;
	...
private:
	std::shared_ptr<PersonImpl> pImpl;						// 구현 클래스 객체에 대한 포인터(스마트 포인터)
															// Person의 사용자는 세부 구현사항과 완전히 갈라서게 되어 재컴파일 할 필요가 없어진다.
															// Person 클래스에 대한 구현 클래스 부분은 자유롭게 수정이 가능해진다.
};

// 인터페이스와 구현을 둘로 나누기 위해서는 정의부에 대한 의존성을 선언부에 대한 의존성으로 바꾸어 놓는 데 있다.
// 위와 같은 Person 클래스를 핸들 클래스라고 한다.