#include<iostream>
#include<string>

class TextBlock
{
public:
	TextBlock(const char* txt)
		: text(txt){}

	const char& operator[](std::size_t position) const		// 변수 position을 받아서 const char 참조자를 반환하는 []연산자 오버로딩(상수 멤버)
		{ return text[position]; }							// 반환한 값을 수정할 수 없고, 참조자를 반환하기 때문에 값이 복사되어 반환되지 않는다.
															// 파라미터 우측의 const는 함수 내에서 이 함수를 호출한 TextBlock 객체 자체를 const화 
															// 시키기 때문에 객체의 멤버 함수에 값을 대입할 수 없다.

	char& operator[](std::size_t position)					// char 참조자를 반환하는 []연산자 오버로딩(비상수 멤버)
		{ return text[position]; }							// 참조자를 반환하기 때문에 반환한 값을 의도한 대로 수정할 수 있다.
private:
	std::string text;
};

void print(const TextBlock& ctb)							
{
	std::cout << ctb[0];									// TextBlock::operator[]의 상수 멤버를 호출한다.
}

int main()
{
	TextBlock tb("Hello");

	std::cout << tb[0];										// TextBlock::operator[]의 비상수 멤버를 호출한다.

	const TextBlock ctb("World");
	print(ctb);

	return 0;
}