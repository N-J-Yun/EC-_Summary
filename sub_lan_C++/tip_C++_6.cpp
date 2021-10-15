// class HomeForSale													// 복사가 되면 안되는 각 객체는 unique한 클래스
// {
// public:
// private:
// 	HomeForSale(const HomeForSale&);								// 복사생성자를 private으로 선언하여 기본 복사 생성자가 public으로 
// 																	// 자동 생성되는 것을 막았고, 외부에서의 복사생성자 호출을 막았다.
// 																	// 하지만 멤버 함수 및 friend 함수가 접근하는 것을 막을 수 없기 때문에
// 																	// 선언만 하고 정의를 하지 않아 링크 시점 에러가 발생하게 유도하였다.
// 																	// (정확하게는 외부에서는 컴파일 에러, friend 및 멤버 함수에서는 링크 에러)

// 	HomeForSale& operator=(const HomeForSale&);						// 위와 같은 원리로 복사 대입 연산자를 정의하였다.	
// };


// 링크 시점 에러를 컴파일 시점 에러로 유도하는 방법
class Uncopyable
{
protected:															// 파생(derived)된 객체에 대해서
	Uncopyable() {}													// 생성과
	~Uncopyable() {}												// 소멸을 허용하고
private:
	Uncopyable(const Uncopyable&);									// 복사는 방지한다.
	Uncopyable& operator=(const Uncopyable&);						
};

class HomeForSale: private Uncopyable {};							// HomeForSale 객체의 복사를 외부에서 시도하려고 할 때
																	// 컴파일러가 기본 복사 생성자와 복사 대입 연산자를 만들려고 시도한다.
																	// 이 과정에서 컴파일러는 base 클래스(Uncopyable)의 대응 버전을 호출한다.
																	// 하지만 Uncopyable의 복사생성자, 복사대입 연산자는 private으로
																	// 숨겨져 있기 때문에 호출 자체가 통하지 않는다.(복사 시도 시 에러 발생)
	
int main()
{
	HomeForSale h1;
	HomeForSale h2;

	HomeForSale h3(h1);												// 복사 생성자 호출(에러 발생)

	h1 = h2;														// 복사 대입 연산자 호출(에러 발생)

	return 0;
}