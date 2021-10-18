class Base
{
public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	...
};

class Derived: private Base
{
public:
	virtual void mf1()								
		{ Base::mf1(); }							// 전달 함수(forwarding function)이다. 가려진 이름을 다시 볼 수 있게 하는 기법
	...												// 암시적으로 inline 함수이다.
};

int main()
{
	Derived d;
	int x;

	d.mf1();										// Derived::mf1() 호출(Base::mf1())

	d.mf1(x);										// error, Base::mf1(int)은 가려져 있다.

	return 0;
}