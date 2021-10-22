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


// 위 조건문을 특성정보 클래스를 활용해 일단 구현해본 코드
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	if(typeid(typename std::iterator_traits<IterT>::iterator_category)	// 타입 점검 동작이 런타임에 발생한다.
		== typeid(std::random_access_iterator_tag))
	...
}
// IterT의 타입은 컴파일 도중 파악이 되지만, if문은 프로그램 실행 도중에 평가 된다(typeid 때문에). == 시간 낭비 + 코드 비대화
// -> 오버로딩

// 각 case별로 오버로딩된 함수를 사용하도록 하여 컴파일러가 조건처리를 하도록 한다.(적합한 매개변수를 가진 함수를 고르게 하는 방식으로)
// 임의 접근 반복자일 경우
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag)
{
	iter += d;
}

// 양방향 반복자일 경우
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag)
{
	if(d>=0) { while(d--) ++iter; }
	else { while(d++) --iter; }
}

// 입력 반복자일 경우(순방향 반복자는 입력 반복자를 상속받기 때문에 둘다 가능)
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::input_iterator_tag)
{
	if(d < 0) 
	{
		throw std::out_of_range("Negative distance");					// 순방향, 입력 반복자를 음수 거리만큼 이동하려고 하면 예외를 던진다.
	}
	while(d--) ++iter;
}

// case 별로 오버로딩된 doAdvance를 호출하는 Advance 함수
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
																		// iter의 iterator_category에 적합한 doAdvance 버전을 호출
}

// 표준 라이브러리에는 iterator_traits 말고도 여러 종류의 특성정보 클래스를 가지고 있다.