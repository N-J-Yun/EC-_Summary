class CompanyA
{
public:
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
};

class CompanyB
{
public:
	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);
};																		// 메시지를 보내는 회사 클래스들

class MsgInfo { ... };													// 메시지 생성에 사용되는 정보를 담는 클래스

template<typename Company>
class MsgSender
{
public:
	void sendClear(const MsgInfo& info)									// 비암호화된 메시지를 전송
	{
		std::string msg;
		// info로 부터 msg를 만든다.
		company c;
		c.sendCleartext(msg);									
	}

	void sendSecret(const MsgInfo& info){...}							// 암호화된 메시지를 전송
};

template<typename Company>
class LoggingMsgSender: public MsgSender<Company>						// MsgSender템플릿 클래스를 상속받은 로그 기록 템플릿 클래스
{
public:
	void sendClearMsg(const MsgInfo& info)								// 함수 이름도 base 클래스와 겹치지 않게 잘 설계했다.
	{
		// 메시지 전송 전 정보를 로그에 기록합니다.
		sendClear(info);												// 기본 클래스의 함수를 호출하려 하지만 컴파일 되지 않는다.
		// 메시지 전송 후 정보를 로그에 기록합니다.
	}
};

// LoggingMsgSender의 base 클래스는 템플릿 클래스이기 때문에 base 클래스의 타입이 정해지지 않은 상태이다.
// base 클래스의 타입은 인스턴스로 만들어질 때까지 무엇이 될 지 알 수 없기 때문에 컴파일러는 LoggingMsgSender 클래스가 어디서 파생된 것인지 모른다.

// 이런 문제를 해결하는 좋은 방법 1

template<typename Company>
class LoggingMsgSender: public MsgSender<Company>			
{
public:
	void sendClearMsg(const MsgInfo& info)					
	{
		// 메시지 전송 전 정보를 로그에 기록합니다.
		this->sendClear(info);											// 기본 클래스 함수에 대한 호출문 앞에 this-> 를 붙혀서 해결
		// 메시지 전송 후 정보를 로그에 기록합니다.
	}
};


// 이런 문제를 해결하는 좋은 방법 2
template<typename Company>
class LoggingMsgSender: public MsgSender<Company>			
{
public:
	void sendClearMsg(const MsgInfo& info)					
	{
		using MsgSender<Company>::sendClear;							// 컴파일러에게 sendClear함수가 기본 클래스에 있다고 가정하라고 알려준다.
		// 메시지 전송 전 정보를 로그에 기록합니다.
		sendClear(info);									
		// 메시지 전송 후 정보를 로그에 기록합니다.
	}
};

// 이런 문제를 해결할 수는 있지만 좋지 않은 방법

template<typename Company>
class LoggingMsgSender: public MsgSender<Company>	
{
public:
	void sendClearMsg(const MsgInfo& info)			
	{
		// 메시지 전송 전 정보를 로그에 기록합니다.
		MsgSender<Company>::sendClear(info);							// 문제는 해결하지만 호출되는 함수가 가상 함수인 경우에는
																		// 가상 함수 바인딩이 무시되는 문제가 생긴다.						
		// 메시지 전송 후 정보를 로그에 기록합니다.
	}
};