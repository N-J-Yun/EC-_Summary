// 핸들 클래스 방법 대신 다른 방법(인터페이스 클래스)
class Person 													// 인터페이스 클래스 Person
{																// 순수 가상함수를 포함하고 있기 때문에 포인터나 참조자를 통해서만 구현할 수 있다.
public:
	virtual ~Person();
	virtual std::string name() const = 0;
	virtual std::string birthDate() const = 0;
	virtual std::string address() const = 0;						

	static std::shared_ptr<Person>								// 이런 인터페이스 클래스를 사용하기 위해서는 객체 생성 수단이 필요하다.			
		create(const std::string& name 							// -> 생성자 역할을 대신하는 팩토리 함수(가상 생성자)를 static으로 선언하였다.
			, const Date& birthday
			, const Address& addr);
};

class RealPerson: public Person 								// 인터페이스 클래스의 인터페이스를 지원하는 Person 클래스에서 파생된 RealPerson
{
public:
	RealPerson(const std::string& name, const Date& birthday, const Address& addr)
		: theName(name)
		, theBirthDate(birthday)
		, theAddress(addr) {}
	virtual ~RealPerson() {}									// 가상 소멸자

	std::string name() const;
	std::string birthDate() const;
	std::string address() const;

private:
	std::string theName;
	Date theBirthDate;
	Address theAddress;
};

std::shared_ptr<Person> 
Person::create(const std::string& name 							// 팩토리 함수의 구현
	, const Date& birthday
	, const Address& addr)
{
	return std::shared_ptr<Person>
	(new RealPerson(name, birthday, addr));						// 최적화
}

int main()
{
	std::string name;
	Date dateOfBirth;
	Address address;
	...

	std::shared_ptr<Person> pp
		(Person::create(name, dateOfBirth, address));			// Person 인터페이스를 지원하는 객체 한 개를 생성하고
	...
	std::cout << pp->name() << ...;								// Person 인터페이스를 통해 그 객체를 사용한다.

	return 0;
}																// 위에서 생성한 객체는 pp가 유효범위를 벗어날 때 자동으로 삭제

// 인터페이스 클래스를 구현하는 용도로 가장 많이 쓰이는 메커니즘 중 한 가지 방법이었다.
// -> 인터페이스(Person)로부터 인터페이스 명세를 물려받게 만든 후에, 그 인터페이스에 들어 있는 가상 함수를 구현하는 것.