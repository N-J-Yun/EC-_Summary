class Window
{
public:
	virtual void OnResize() {}									// 가상 함수
};

class SpecialWindow: public Window
{
public:
	virtual void OnResize()
	{
		static_cast<Window>(*this).OnResize();					// Window::OnResize가 호출되기는 하지만 *this의 기본 클래스 부분에 대한
																// 사본에 OnResize가 적용되어 현재 객체엔 아무 변화가 없다.
		...
		//Window::OnResize();									// 간단한 해결책
	}
}