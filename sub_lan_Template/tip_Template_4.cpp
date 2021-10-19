class Address {...};
class PhoneNumber {...};
class Person 
{
public:
	...
private:
	std::string name;
	Address address;
	PhoneNumber voidNumber;
	PhoneNumber faxNumber;
};
// Person 객체는 string, Address, PhoneNumber 객체로 이루어져 있다.(has-a 관계)

// 합성(composition)이란?
// layering, containment, aggregation, embedding 등으로도 알려져 있다.

// 소프트웨어 개발에서 다루는 영역(domain)은 두 가지이다.
// 일상생활에서의 사물을 본 뜬 application domain
// 시스템 구현만을 인공물이 속한 implementation domain

// 객체 합성이 application에서 일어나면 has-a 관계(...는 ...를 가짐)
// 객체 합성이 implementation에서 일어나면 is-implemented-in-terms-of 관계(...는...를 써서 구현됨)

template<class T>
class Set
{
public:
	bool member(const T& item) const;

	void insert(const T& item);
	void remove(const T& item);

	std::size_t size() const;

private:
	std::list<T> rep;
};
// Set은 list를 써서 구현됨(is-implemented-in-terms-of 관계)
