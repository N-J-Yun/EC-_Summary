#include<iostream>
#include<string>

class CTextBlock
{
public:
	std::size_t length() const;									// const 멤버 함수 선언

private:
	char* pText = "asdfasdf";

	mutable std::size_t textLength;								// mutable 키워드를 멤버 변수 앞에 선언해 주었다.
	mutable bool lengthIsValid;									// mutable 키워드가 있으면 어떤 순간에서도(const 멤버 함수 내에서도) 수정 가능
};

std::size_t CTextBlock::length() const							// const 멤버 함수 정의
{																
	if (!lengthIsValid)
	{
		textLength = std::strlen(pText);						// mutable 멤버 변수 textLength, lengthIsValid에 값을 대입한다.
		lengthIsValid = true;
	}

	return textLength;
}

int main()
{

	return 0;
}