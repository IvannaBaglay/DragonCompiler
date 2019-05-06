#include "Lexer.h"

std::vector<char> true_s = {
	';','(',')',':',',','.', '<','>','='
};

Lexer::Lexer(std::string sourceFileName)
{
	reserve(Word("IF", IF));
	reserve(Word("ELSE", ELSE));
	reserve(Word("break", BREAK));
	reserve(Word("THEN", THEN));
	reserve(Word("ENDIF", ENDIF));
	reserve(*Word::WordTRUE);
	reserve(*Word::WordFALSE);

	reserve(Word("WHILE", WHILE));
	reserve(Word("ENDWHILE", ENDWHILE));
	reserve(Word("DO", DO));
	
	reserve(Word("PROCEDURE", PROCEDURE));
	reserve(Word("PROGRAM", PROGRAM));
	reserve(Word("BEGIN", BEGIN));
	reserve(Word("END", END));
		
	reserve(*DataType::TypeBLOCKFLOAT);
	reserve(*DataType::TypeSIGNAL);
	reserve(*DataType::TypeCOMPLEX);
	reserve(*DataType::TypeEXT);
	reserve(*DataType::TypeFLOATS);
	reserve(*DataType::TypeINTEGER);

	source.open(sourceFileName.c_str(), std::ios::in); 
	source.unsetf(std::ios::skipws);
	if ((!source.is_open())||(source.eof()))
	{
		std::cout << "Fail to Open File " << sourceFileName << std::endl;
		exit(1);
	}
}
Lexer::~Lexer(void)
{
}
Token* Lexer::scan() 
{	
	for ( ; ; readChar())
	{			
		column = i;
		if (peekChar == EOF)
			return NULL;	
		if (peekChar == ' ' || peekChar == '\t')
		{
			if (peekChar == '\t')
				i += 3;
			continue;
		} else if (peekChar == '\n')
		{
			line++;
			i = 0;
		} else if (peekChar > 0)
		{
			break;
		}
	}
	bool flag = false;
	for (std::vector<char>::iterator iter = true_s.begin(); iter != true_s.end(); iter++)
	{
		if ((peekChar == *iter) || (isalpha(peekChar)) || (isdigit(peekChar)))
		{
			flag=true;
			break;
		}
	}
	if(!flag) {
		std::cerr << "Lexer:Error (line: " << line << ",column: " << i << ")  error symbol" << std::endl;
		system("pause");
		exit(1);
	}
	switch(peekChar) {
	case '(':
		column = i;
		if (readChar('*'))
		{			
			while (true)
			{
				readChar();
				
				if (peekChar == EOF)
				{
					std::cerr << "Lexer:Error (line: " << line << ",column: " <<i<< ")  unexpected end of file found in comment"<< std::endl;
					system("pause");
					exit(1);
					return NULL;
				}
				if (peekChar == '\n')
				{
					line++;
					column = 0;
					i = 0;
				}
				while (peekChar=='*')
					if (readChar(')'))
						return scan();
			}
		}
		else
			return new Token('(');
		break;	
	case '<':
		if (readChar('='))
		{
			//std::cout << (*Word::WordLE);
			return Word::WordLE;
		}
		else {
			//std::cout << Token('<');
			return new Token('<');
		}
		break;
	case '>':
		if (readChar('='))
		{
			//std::cout << (*Word::WordGE);
			return Word::WordGE;
		}
		else {
			//std::cout << Token('>');
			return new Token('>');
		}
		break;
	default:	
		break;		
	}
	if (isdigit(peekChar))
	{		
		int v = 0;
		do
		{
			v = v*10 + (peekChar-'0');
			readChar();
		} while (isdigit(peekChar));
		if (peekChar != '.')
		{	
			std::cout<<"Int Value\t"<<v<<std::endl;
			return new Num(v);
		}
		float f = (float)v;
		float d = 10;
		while(isdigit(peekChar)) {
			f = f + (float)(peekChar-'0')/d;
			d = d * 10;
		}
		return new Real(f);
	}
	if (isalpha(peekChar))
	{		
		std::stringstream idSS;
		do
		{
			idSS<<peekChar;
			readChar();
		} while ((isalpha(peekChar))||(isdigit(peekChar)));
		std::string id = idSS.str();
		Word* w = findByString(id);
		if (w == Word::WordNULL)
		{
			Word* idWord = new Word(id, ID);
			reserve(*idWord);
			return idWord;
		} 
		return w;
	}
	Token* tok = new Token(peekChar);
	peekChar = ' ';
	return tok;
}
void Lexer::reserve(Word w) {
	words.push_back(w);
}
Word* Lexer::findByString(std::string& str) {
	for (std::vector<Word>::iterator iter = words.begin(); iter != words.end(); ++iter)	
		if (iter->w_lexme.compare(str) == 0)
			return &(*iter);			
	return Word::WordNULL;
}
void Lexer::readChar() 
{
	i++;
	if (source.eof())
		peekChar = EOF;
	else if (source.good())
		source>>peekChar;	
}
bool Lexer::readChar(char c) 
{
	readChar();
	//i--;
	if (peekChar != c || peekChar == EOF)
		return false;
	peekChar = ' ';
	return true;
}