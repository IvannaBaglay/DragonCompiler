#include "Token.h"
#include <sstream>

Token::Token()
{

}
Token::Token(Tag t): t_tag(t)
{

}

Token::Token(char t): t_tag((Tag)t)
{

}
Token::~Token(void)
{
}
std::string Token::toString() const
{
	std::stringstream result;
	result << (char)t_tag;
	return result.str(); 
}
std::ostream& operator<<(std::ostream& os, const Token& tok)
{
	os<<tok.toString()<<"\n";
	return os;
}
Num::Num(int val):Token(NUM), n_value(val)
{
}
Num::~Num()
{
}
std::string Num::toString() const
{
	std::stringstream result;
	result<<n_value;
	return result.str();
}
std::ostream& operator<<(std::ostream& os, const Num& tok)
{
	os << tok.toString() << "\n";
	return os;
}
Real::Real(float val):Token(REAL), r_value(val) 
{
}
Real::~Real()
{
}
std::string Real::toString() const
{
	std::stringstream result;
	result<<r_value;
	return result.str();
}
std::ostream& operator<<(std::ostream& os, const Real& tok)
{
	os << tok.toString() << "\n";
	return os;
}