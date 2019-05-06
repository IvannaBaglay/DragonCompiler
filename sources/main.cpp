
#include "Lexer.h"
#include "Parser.h"
#include "Node.h"
#include"Generate.h"
#include <fstream>

std::ofstream intermediaRepresentStream;

void test(Lexer *lex, const char *str)
{
	intermediaRepresentStream.open(str, std::ios::out);
	if (!intermediaRepresentStream.is_open())
	{
		std::cout << "Fail to Open File for Output IR" << std::endl;
		exit(1);
	}
	Parser parser(lex);
	Node *root = NULL;
	root = parser.signal_program(root);
	root->treeprint(root, 0);
	Generate generate(root);
	intermediaRepresentStream.close();
}

int main() 
{
	//true-test
	std::cout << "true test\n";
	system("pause");
	test(new Lexer("sample.dc"), "sample.asm");
	std::cout << "\n\n*****************************************************\n\n";
	test(new Lexer("sample1.dc"), "sample1.asm");
	std::cout << "\n\n*****************************************************\n\n";
	test(new Lexer("sample2.dc"), "sample2.asm");
	std::cout << "\n\n*****************************************************\n\n";
	test(new Lexer("sample3.dc"), "sample3.asm");
	std::cout << "\n\n*****************************************************\n\n";
	test(new Lexer("sample4.dc"), "sample4.asm");
	std::cout << "\n\n*****************************************************\n\n";
	

	//false-test
	std::cout << "false test\n";//транслятор припиняє роботу щойно було знайдено помилку
	system("pause");
	test(new Lexer("sample_f.dc"), "sample_f.asm");
	//std::cout << "\n\n*****************************************************\n\n";
	//test(new Lexer("sample1_f.dc"), "sample1_f.asm");
	//std::cout << "\n\n*****************************************************\n\n";
	//test(new Lexer("sample2_f.dc"), "sample2_f.asm");
	//std::cout << "\n\n*****************************************************\n\n";
	//test(new Lexer("sample3_f.dc"), "sample3_f.asm");
	//std::cout << "\n\n*****************************************************\n\n";
	//test(new Lexer("sample4_f.dc"), "sample4_f.asm");
	std::cout << "\n\n*****************************************************\n\n";
	
	system("pause");
	return 0;
}

