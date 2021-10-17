namespace WebBrowserStuff
{
	class WebBrowser { ... };

	void clearBrowser(WebBrowser& wb);			// 편의함수, 멤버도, 프렌드도 아니기에 사용자 수준에서 충분히 구현할 수 있다.
												// 그저 편의를 위해서 제공하기 때문에 편의함수라 부른다.
												// WebBrowser처럼 응용도가 높은 클래스는 이러한 편의함수가 많이 생길 수 있다.
												// 따라서 기능별로 파일을 나눠 같은 네임 스페이스 안에서 구현함으로써 
												// 사용자는 필요한 기능이 있는 헤더만 #include하여 사용할 수 있다!
	
												// 대부분의 C++ 표준 라이브러리들이 이런 구조로 구성되어 있다!(std네임스페이스)
}

// 네임스페이스의 가장 중요한 특징 : 여러 개의 소스파일에 나뉘어 흩어질 수 있다.

//---------------------------"WebBrowser.h" WebBrowser 클래스 자체에 대한 헤더----------------------------------------

namespace WebBrowserStuff
{
	class WebBrowser { ... };
	...
}

//---------------------------"WebBrowserbookmarks.h" ----------------------------------------

namespace WebBrowserStuff
{
	...											// 즐겨찾기 관련 편의 함수들이 들어간다.
}

//---------------------------"WebBrowsercookies.h" ----------------------------------------

namespace WebBrowserStuff
{
	...											// 쿠키 관련 편의 함수들이 들어간다.
}

