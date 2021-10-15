class Foo
{
public:
	Foo(const &Foo rhs);
	Foo& operator=(const &Foo rhs);
private:
	int a;
};

class Foobar : public Foobar										
{
public:
	Foobar(const &Foobar rhs);
	Foobar& operator=(const &Foobar rhs);
private:
	int b;
};

Foobar::Foobar(const &Foobar rhs)									// 파생 클래스의 복사함수(복사생성자, 복사대입연산자)를 구현할 때는
	: Foo(rhs)														// base 클래스의 복사함수를 활용하여
	, b(rhs.b){}													// 객체의 모든 부분을 빠짐없이 복사하자!
Foobar& Foobar::operator=(const &Foobar rhs)
{
	Foo::operator=(rhs);
	b = rhs.b;

	return *this;
}