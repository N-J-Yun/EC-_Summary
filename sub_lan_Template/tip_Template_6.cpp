// typename과 typedef를 함께 쓸 때

template<typename IterT>
void workWithIterator(iterT iter)
{
	//typename std::iterator_traits<IterT>::value_type temp(*iter);			// 이런 타입을 여러번 치기 번거로우므로 typedef를 사용하자

	typedef typename std::iterator_traits<IterT>::value_type value_type;	// typename으로 타입임을 알려준 뒤 typedef로 묶어주면 된다.
	value_type temp(*iter);
	...
}