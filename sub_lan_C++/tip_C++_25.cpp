class Window{...};

... 		// 많은 파생클래스들

int main()
{
	typedef std::vector<std::shared_ptr<Window> > VPW;

	VPW winPtrs;

	for(VPW::iterator iter = winPtrs.begin(); iter!=winPtrs.end(); ++iter)
	{
		if(SpecialWindow1 *psw1 =
			dynamic_cast<SpecialWindow1*>(iter->get())) {...}

		else if(SpecialWindow2 *psw1 =
			dynamic_cast<SpecialWindow2*>(iter->get())) {...}

		else if(SpecialWindow3 *psw1 =
			dynamic_cast<SpecialWindow3*>(iter->get())) {...}						// 크기만 하고 속도도 둔하고 망가지기 쉽다.
																					// 클래스 계통이 바뀌면(파생 클래스가 추가되면)
																					// 위에 새로운 분기문을 또 추가시켜야한다.
		...																			// 분기문 + dynamic_cast = 엄청난 속도
	}
	return 0;																		// 캐스팅은 엥간해선 쓰지말고 굳이 써야겠다면
																					// 최대한 격리시켜놓고 사용하고, 인터페이스로 막아두자.
}
