struct Day
{
	explicit Day(int d)
		: val(d) {}
	int val;
};

struct Month
{
	explicit Month(int m)
		: val(m) {}
	int val;
};

class Month														// Month는 1~12밖에 없으므로 타입의 값에 제약을 가해도 괜찮다.
{																// enum,int 대신 타입 안전성을 위해 지역 정적 객체로 정의
public:
	static Month Jan() { return Month(1); }
	static Month Feb() { return Month(2); }
	static Month Mar() { return Month(3); }
	...
private:
	explicit Month(int m);										// Month 값이 새로 생성되지 않도록 private으로 생성자 선언(정의 X)
};

struct Year
{
	explicit Year(int y)
		: val(y) {}
	int val;
};

// class Date														// 문제가 없어 보이지만 사용자가 실수할 가능성이 매우 높은 인터페이스
// {
// public:
// 	Date(int month, int day, int year);							// 이상한 값이 월,일에 들어올 수 있고, 매개변수를 바꿔서 전달할 수 있다.
// };

class Date						
{
public:
	Date(const Month& m, const Day& d, const Year& y);			// 연,월,일 순서를 헷갈리지 않게 각각의 래퍼 타입을 새로 만들어 인터페이스 수정 
	...															// 사용자가 엉터리로 쓰기에 어렵게 만들었다.
};

int main()
{
	Date d(30, 3, 1995);										// 타입 에러: int가 아니라, 각 래퍼 타입으로 입력해야 한다.
	Date d(Day(30), Month(3), Year(1995));						// 타입 에러: Day <-> Month

	Date d(Month(3), Day(30), Year(1995));						// 에러: 호출할 수 없는 생성자
	Date d(Month::Mar(), Day(30), Year(1995));					// ok

	return 0;
}
