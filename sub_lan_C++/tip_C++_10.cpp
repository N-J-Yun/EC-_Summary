class Bitmap{...};

class Widget
{
	private: Bitmap *pb;
};

Widget& Widget::operator=(const Widget& rhs)    						// 안전하지 않게 구현된 operator=
{
	delete pb;															// 자기대입이 발생한 상황이라면? 
	pb = new Bitmap(*rhs.pb);											// 본인을 삭제함과 동시에 rhs도 사라져서 dangling pointer 발생(메모리 누수)
	return *this;
}

Widget& Widget::operator=(const Widget& rhs)							// 일치성 테스트 추가
{
	if(this == &rhs) return *this;										// rhs와 *this가 같다면 자기자신을 return한다.
																		// 하지만 이러한 방식은 코드의 효율(분기로 인한 파이프라이닝 성능저하 등)
																		// 측면과 예외 안전성 측면에서 좋지 않다.
	delete pb;
	pb = new Bitmap(*rhs.pb);											// 이 부분에서 예외가 터지게 되면(동적 메모리 부족 등)
																		// widget 객체는 결국 삭제된 bitmap포인터를 가지고 혼자 남게 된다.

	return *this;
}

Widget& Widget::operator=(const Widget& rhs)							// 해결책 1
{
	Bitmap *pOrig = pb;													// 임시 Bit객체를 하나 만들어 원래의 pb를 복사해 두어 문제를 해결한다.
	pb = new Bitmap(*rhs.pb);
	delete pb;

	return *this;
}

// 매우 효율적인 해결책(Copy and Swap 기법 활용)
class Widget
{
	void swap(Widget& rhs);												// *this와 rhs의 데이터를 맞바꾼다. 여러 대입연산자 오버로딩에서 재사용가능
};

Widget& Widget::operator=(const Widget& rhs)							
{	
	Widget temp(rhs);
	swap(temp);
	return *this;
}

int main()
{
	Widget w;
	w = w;																// 자기 대입의 바보같은 예시
	//*px = *pv;														// 자기 대입이 발생할 가능성이 있는 현실성 있는 예시

	return 0;
}