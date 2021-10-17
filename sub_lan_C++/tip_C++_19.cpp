class WebBrowser
{
public:
	...
	void clearCache();									
	void clearHistory();
	void removeCookies();
	...

	void clearEverything();											// 멤버 함수
};

void clearBrowser(WebBrowser& wb)									// 비멤버 비프렌드 함수
{
	wb.clearCache();
	wb.clearHistory();
	wb.removeCookies();
}

// 같은 기능을 가진 비멤버 비프렌드 함수가 멤버 함수보다 더 낫다.

// 캡슐화 측면에서 보면
// 멤버 함수는 private멤버에 접근할 수 있다.
// 어떤 데이터에 접근할 수 있는 함수가 많다는 것은 그만큼 캡슐화가 덜 된다는 것이다.

// 비멤버 비프렌드 함수는 어떤 클래스의 private 멤버 부분을 접근할 수 있는 함수의 개수를 늘리지 않는다.
// => 캡슐화의 정도가 더 높다.
