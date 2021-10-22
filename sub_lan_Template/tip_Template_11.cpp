// 태그 구조체: 다섯 개의 iterator category를 식별하는 데 쓰이며, is-a 관계이다.
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// 이상적인 advance 구현 형태
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	if(iter가 임의 접근 반복자이다)										// random_access iterator는 상수 시간 연산이 가능하다.
		iter += d;
	else																// 그 외 4개는 불가능
	{
		if ( d >= 0 ) { while(d--) ++iter; }			
		else { while (d++) --iter; }
	}
}
// 위처럼 구현하기 위해서는 iter가 어떤 iterator 타입인지를 알아야 할 필요가 있다.
// 타입에 대한 정보를 얻어낼 필요가 있다.
// -> 특성정보(traits), 컴파일 도중에 어떤 주어진 타입의 정보를 얻을 수 있게 하는 객체
// 하지만 특수한 문법도 키워드도 아니고 그저 구현 기법 중 하나이다. 
// 특성정보는 기본제공 타입과 사용자 정의 타입에서 모두 돌아가야한다. 구조체로 구현하는 것이 관례이다.

// 사용자 정의 iterator 타입은 iterator_category라는 이름의 typedef타입을 내부에 가져야 하며 해당 태그 구조체에 대응되어야 한다.
template<...>
class deque
{
public:
	class iterator
	{
	public:
		typedef random_access_iterator_tag iterator_category;			// deque의 iterator 범주는 임의 접근 iterator이다.
		...
	};
	...
};

// 그리고 위의 iterator 클래스가 가진 typedef 타입을 똑같이 구현한 것이 iterator_traits이다.
template<typename IterT>
struct iterator_traits
{
	typedef typename IterT::iterator_category iterator_category;
	...
};

// 하지만 위 코드는 기본 제공 타입(여기서는 포인터)에 대해서는 제대로 돌아가지 않는다.
// 포인터 타입의 iterator를 지원하기 위해 부분 템플릿 특수화 버전을 제공한다.
template<typename IterT>
struct iterator)traits<IterT*>
{
	typedef random_access_iterator_tag iterator_category;
	...
};





