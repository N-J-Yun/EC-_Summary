class Timer
{
public:
	explicit Timer(int tickFrequency);					// 호출 주기를 입력받는 명시적 생성자
	virtual void onTinck()const;						// 일정 시간이 경과할 때마다 자동으로 이 함수가 호출된다.
	...
};

class Widget: private Timer								// private으로 상속하여 timer의 모든 멤버가 모두 private 멤버가 되었다.
{
private:
	virtual void onTick() const; 						// Widget 클래스에서 onTick함수를 사용할 수 있다.
	...
};

// private 상속은 is-implemented-in-terms-of 관계이다.
// private 상속을 하면 base의 모든 멤버가 파생 클래스에서는 private 멤버가 된다.

// 하지만 private 상속을 쓰기보다는 객체 합성과 public 상속으로 구현하는 것이 좀더 괜찮다.
class Widget
{
private:
	class WidgetTimer: public Timer 					// 중첩 클래스를 private에 구현하여 사용
	{
	public:
		virtual void onTick() const;
		...
	};
	WidgetTimer timer;
	...
};

// 이렇게 구현하면 Widget의 파생클래스는 WidgetTimer에 접근할 수 없어서 재정의 할 수 없다.
// WidgetTimer의 정의를 Widget으로부터 빼내고 Widget이 WidgetTimer 객체에 대한 포인터만 갖도록 만들어 두면 컴파일 의존성도 피할 수 있다.
// 최대한 대안을 고민하여 어쩔 수 없을 때만 private 상속을 사용하자.
