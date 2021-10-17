template<typename T>
void doSomething(T& obj1, T& obj2)
{
	using std::swap;										 
	...
	swap(obj1, obj2);											// ADL(Argument Dependent Lookup)규칙에 의해
																// 1. 전역 or 타입 T와 동일한 네임스페이스 안에 T전용 swap이 있는지 찾는다.
																// 2. 없으면, using 선언에 의해 std::swap의 T전용 버전을 찾는다.
																// 3. 없으면, std::swap 일반 버전을 호출한다.
	...
}

