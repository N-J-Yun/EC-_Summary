#include<iostream>
#include<string>
 
class TextBlock
{
public:
	const char& operator[](std::size_t position) const			
	{
		//.....  경계 검사										// 멤버 함수에 mutable 선언을 해주었기 때문에 
		//.....  접근 데이터 로깅									// 로깅 작업 같은 멤버 변수 수정이 가능하다.
		//.....   자료 무결성 검증
		return pText[position];
	}

	char& operator[](std::size_t position)						// 비상수 버전 1.
	{
		//.....  경계 검사										// 하지만 같은 기능의 함수가 const 멤버 함수가 아니라는 이유로
		//.....  접근 데이터 로깅									// 다른 버전으로 오버로딩되어 코드 중복이 심각하게 일어나고 있다.
		//.....   자료 무결성 검증								
		return text[position];
	}

	// 															// 비상수 버전 2.
	// char& operator[](std::size_t position)					// 상수 operator[] 함수에서 값을 얻어와 const를 떼고 반환하는 버전
	// {
	// 	return const_cast<char&>(								// 상수 operator[] 에서 반환된 값에서 const를 떼어내는 캐스팅(const char& -> char&)
	// 		static_cast<const TextBlock&>						// (*this)에 const를 붙이는 캐스팅 (TextBlock& -> const TextBlock&)
	// 			(*this)[position]								// 코드가 더럽고, 생각하기 어렵고, 좋지 않은 코딩방식(const_cast 사용)이지만
	// 	);														// 코드 중복을 효과적으로 피할 수 있다.
	// }

private:
	char* pText;

	mutable std::size_t textLength;								// mutable 키워드를 멤버 변수 앞에 선언해 주었다.
	mutable bool lengthIsValid;									
};

int main()
{

	return 0;
}