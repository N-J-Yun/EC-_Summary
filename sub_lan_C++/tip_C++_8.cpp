class DBConnection
{
public:
	static DBConnection create();								// DBConnection 객체를 생성하여 반환한다.

	void close();												// 연결을 닫는다. 실패하면 예외를 던짐.
};

class DBConn  													// DBConnection 관리자 클래스
{
public:
	~DBConn()													// 데이터베이스 연결이 항상 닫히도록 해주는 소멸자
	{
		db.close();												// 만약 여기서 예외가 발생한다면?
																// 예외의 catch를 다른 곳에서 한다면 소멸자가 자원 해제를 올바르게 하지 못한다.
	}
};

// // 해결책 1: 예외 발생 시 프로그램 종료(abort)
// // 못 볼꼴을 미리 막아버릴 수 있다.
// DBConn::~DBConn()
// {
// 	try{db.close();}
// 	catch(...) 
// 	{
// 		//close 호출 실패 log
// 		std::abort();
// 	}
// }

// // 해결책 2: close를 호출한 곳에서 일어난 예외를 삼켜버린다.
// // 무엇이 잘못됐는지를 알려주는 정보가 묻혀버린다.
// // 하지만 예외를 무시한 뒤 프로그램이 신뢰성 있게 실행을 지속할 수 있다면 괜찮다.
// DBConn::~DBConn()
// {
// 	try{db.close();}
// 	catch(...) 
// 	{
// 		//close 호출 실패 log
// 	}
// }

// // 사용자가 처리할 기회를 주는 해결책
// 숨겨진 DBConnection 클래스가 아닌 사용자가 사용할 수 있는 DBConn 클래스에
// 예외를 발생시킬 수 있는 close 함수를 제공하여 사용자가 직접 처리할 수 있게 한다.
// 사용자가 처리 안하고 넘어가면 해결책 1,2로 넘어간다.
// class DBConn
// {
// public:
// 	void close()
// 	{
// 		db.close();
// 		closed = true;
// 	}
// 	~DBConn()
// 	{
// 		if(!closed)
// 			try
// 			{
// 				db.close();
// 			}
// 			catch
// 			{
// 				// 해결책 1 or 2
// 			}
// 	}
// private:
// 	DBConnection db;
// 	bool closed;
// };

int main()
{
	DBConn dbc(DBConnection::create());

	return 0;
}