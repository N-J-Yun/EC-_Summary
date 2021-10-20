template<typename T, std::size_t n>										// T라는 타입 매개변수와 size_t타입의 비타입 매개변수도 받는다.
class SquareMatrix
{
public:
	void invert();														// 역행렬로 만든다.
};

int main()
{
	SquareMatrix<double, 5> sm1;

	sm1.invert();

	SquareMatrix<double, 10> sm2;

	sm2.invert();														// invert()의 사본이 인스턴스화 될 때 만들어지는 사본의 갯수는 2개이다.
																		// 두 사본은 서로 다른 함수이지만 상수만 빼면 완전히 똑같다.
																		// ->템플릿을 포함한 프로그램이 코드 비대화를 일으키는 일반적인 형태이다.
	return 0;															// 똑같은 내용의 코드와 데이터가 여러 벌로 중복되어 이진 파일로 구워진다는 뜻
}

// 위 문제를 해결하기 위한 방법
// 행렬 크기를 매개변수로 받는 별도의 함수를 만들고, 그 함수에 값을 넘겨서 호출하게 만들자.
template<typename T>
class SquareMatrixBase													// 행렬 크기에 독립적인 base 클래스
{
protected:																// 파생 클래스에서 코드 복제를 피할 목적으로만 만들었기 때문에 protected
	void invert(std::size_t matrixsize);								// 행렬 크기를 매개변수로 받아서 역행렬로 만든다.
};

template<typename T, std::size_t n>
class SquareMatrix: private SquareMatrixBase<T>							// 파생 클래스의 구현을 돕기 위해서만 base 클래스를 만들었기 때문에
																		// is implemented in terms of 관계인 private 상속을 사용
{
private:
	using SquareMatrixBase<T>::invert;									// 기본 클래스의 invert가 가려지는 것을 막았다.
public:
	void invert() { invert(n); }										// 위의 using문으로 base의 invert가 존재함을 컴파일러에게 알렸다.
																		// base의 invert에 대해 인라인 호출을 수행한다.
};

// 하지만 아직 SquareMatrixBase::invert 함수는 자신이 상대할 데이터가 어떤 것인지 알 수가 없다.
// 이 정보를 가진 쪽은 파생 클래스밖에 없기 때문.

// 이 문제를 해결하는 좋은 방법
// 행렬 값을 담는 메모리에 대한 포인터를 SquareMatrixBase가 저장하도록 하는 것
template<typename T>
class SquareMatrixBase
{
protected:
	SquareMatrixBase(std::size_t n, T *pMem)							// 행렬 크기, 행렬 값에 대한 포인터를 저장하는 생성자.
		: size(n)
		, pDatea(pMem) {}

	void setDatePtr(T *ptr) { pData = ptr; }
private:
	std::size_t size;
	T *pData;
};
// 메모리 할당 방법의 결정 권한이 파생 클래스 쪽으로 넘어가게 된다.
// 파생 클래스를 만드는 사람에 따라 행렬 데이터를 SquareMatrix 객체 안에 데이터 멤버로 직접 넣는 것으로 결정할 수도 있다.
template<typename T, std::size_t n>
class SquareMatrix: private SquareMatrixBase<T>
{
public:
	SquareMatrix()
		:SquareMatrixBase<T>(n, data) {}								// 행렬 크기 및 데이터 포인터를 기본 클래스로 올려 보낸다.
private:
	T data[n*n];														// 정적 배열로 선언했지만 객체 자체의 크기가 커지는 게 맘에 안들면
};																		// 힙에 저장하는 방식을 사용할 수도 있다.

// 기존 코드의 경우 행렬 크기가 컴파일 시점에 투입되는 상수이기 때문에 상수 전파 등의 최적화가 먹혀들기 좋다. 하지만 코드 비대화의 문제가 있다.
// 아래 코드의 경우 코드 비대화의 문제를 해결할 수 있다.(이것이 캐시 활용 및 페이징 성능을 올려준다.) 하지만 상수 전파 최적화는 얻어낼 수 없다.

// 비타입 템플릿 매개변수로 생기는 코드 비대화의 경우, 템플릿 매개변수를 함수 매개변수 혹은 클래스 데이터 멤버로 대체함으로써 비대화를 종종 없앨 수 있다.
// 타입 매개변수로 생기는 코드 비대화의 경우, 동일한 이진 표현구조를 가지고 인스턴스화 되는 타입들(포인터, int&long 등)이 한 가지 함수 구현을
// 공유하게 만듦으로써 비대화를 감소시킬 수 있다.