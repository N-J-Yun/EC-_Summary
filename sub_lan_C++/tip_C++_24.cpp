class Window{...};
class SpecialWindow: public Window
{
public:
	void blink();
	...
};

// 기본적으로 dynamic_cast는 상당수의 구현환경에서 정말 느리게 구현되어 있다.

int main()
{
	typedef std::vector<std::shared_ptr<Window> > VPW;

	VPW winPtrs;
	...
	for(VPW::iterator iter = winPtrs.begin();											// VPW의 iterator를 사용해
		iter != winPtrs.end();
		++iter)
	{
		if(SpecialWindow *psw = dynamic_cast<SpecialWindow*>(iter->get()))				// dynamic_cast로 iter를 SpecialWindow*로 캐스팅하여
			psw->blink();																// SpecialWindow::blink()를 호출하였다.
	}
	return 0;
}


// 더 깔끔한 구현
// class Window
// {
// public:
// 	virtual void blink() {}																// 기본 blink를 가상함수로 제공하였다.
// };
// class SpecialWindow: public Window
// {
// public:
// 	virtual void blink();
// 	...
// };

// int main()
// {
// 	typedef std::vector<std::shared_ptr<SpecialWindow> > VSPW;						// VSPW의 포인터를 담는 vector를 선언했다.

// 	VSPW winPtrs;
// 	...
// 	for(VSPW::iterator iter = winPtrs.begin();										// VSPW의 iterator를 사용해
// 		iter != winPtrs.end();
// 		++iter)
// 		(*iter)->blink();															// 캐스탱 없이 blink 호출
// 	return 0;
// }
