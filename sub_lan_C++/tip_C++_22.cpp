std::string encryptPassword(const std::string& password)
{
	std::string encrypted;												// RAII 하지 않았고, 후에 사용되지 않을 가능성도 있음.
	if(password.length() < minimumPasswordLength)						// 만약 여기서 예외가 발생한다면 encrypted는 사용되지 않고
		throw logic_error("pw is too short");							// 쓸데없는 비용이 생긴다.
	...
	return encrypted;
}

void encrpyt(std::string& s);											// string참조자를 입력받는 암호화 함수

std::string encryptPassword(const std::string& password)				// encryptPassword의 최적화 버전
{
	if(password.length() < minimumPasswordLength)						// 예외 발생여부에 따라 encrypted 변수의 비용 발생 여부가 달라진다.
		throw logic_error("pw is too short");

	std::string encrypted(password);									// RAII로 쓸데없는 생성자 호출을 없앴다.

	encrpyt(encrypted);
	return encrypted;
}
