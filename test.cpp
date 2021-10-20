// 태그 구조체
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	if(iter가 임의 접근 반복자이다)
		iter += d;
	else
	{
		if ( d >= 0 ) { while(d--) ++iter; }
		else { while (d++) --iter; }
	}
}

template<...>
class deque
{
public:
	class iterator
	{
	public:
		typedef random_access_iterator_tag iterator_category;
		...
	};
	...
};

template<...>
class list
{
public:
	class iterator
	{
	public:
		typedef bidirectional_iterator_tag iterator_category;
		...
	};
	...
};

template<typename IterT>
struct iterator_traits
{
	typedef typename IterT::iterator_category iterator_category;
};

