#include <iostream>
#include "Token.h"
#include "Scanner.h"

void testTokenClass()
{
	TokenType tt = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass tok1(tt, lexeme);
	std::cout << tok1 << std::endl;
};
void testScannerClass()
{
	ScannerClass scanner("basic_test.txt");
	TokenClass token;
	while(token.GetTokenType() != ENDFILE_TOKEN)
	{
		scanner.GetNextToken();
		std::cout<<token<<std::endl;
	};

};

int main()
{
	testTokenClass();
	testScannerClass();
	system("pause");
	return 0;
};
