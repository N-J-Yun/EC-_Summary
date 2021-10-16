FontHandle getFont();

void releaseFont(FontHandle fh);

class Font 														// RAII 클래스
{
public:
	explicit Font(FontHandle fh) 								// 자원(폰트)을 획득한다.
		: f(fh) {}
	~Font() { releaseFont(f); }

	FontHandle get() const { return f; }						// 1. 명시적 변환 함수
	FontHandle operator() const { return f; }					// 2. 암시적 변환 함수
private:
	FontHandle f;												// 실제 폰트(자원)
};

void changeFontSize(FontHandle f, int newSize);					// 실제 폰트자원(FontHandle)을 직접 사용해야하는 API
																// 자원 관리 객체(Font)를 실제 폰트자원 객체(FontHandle) 로 변환할 방법이 필요
																// 1. 명시적 변환 방법, 2. 암시적 변환 방법
int main()
{
	Font f(getFont());
	int newFontSize;

	...

	changeFontSize(f.get(), newFontSize);						// 명시적 변환 방법, 안전하지만 귀찮다.
	changeFontSize(f, newFontSize);								// 암시적 변환 방법, 편하지만 자원 관리 객체(Font)를 사용하려고 한 부분에서
																// 의도치 않게 자원 객체(FontHandle)로 바뀌어 버리는 위험성이 존재한다.
	return 0;
}
