class Base
{
private:
	int x;

public:
	virtual void mf1() = 0;
	virtual void mf1(int);
	virtual void mf2();
	void mf3();
	void mf3(double);
	...
};

class Derived: public Base
{
public:
	using Base::mf1;								// Base에 있는 것들 중 mf1과 mf3을 이름으로 가진 것들을
	using Base::mf3;								// Derived의 유효범위에서 볼 수 있도록(public으로) 만듭니다

	virtual void mf1();
	void mf3();
	void mf4();
	...
};

int main()
{
	Derived d;
	int x;

	d.mf1();										// Derived::mf1() 호출
	d.mf1(x);										// Base::mf1(int) 호출

	d.mf2();										// Base::mf2() 호출

	d.mf3();										// Derived::mf3() 호출
	d.mf3(x);										// Derived::mf3(double) 호출

	return 0;
}