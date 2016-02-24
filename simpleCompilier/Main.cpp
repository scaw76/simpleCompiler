#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Debug.h"

void testTokenClass()
{
	TEST("Print void token");
	TokenType tt = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass tok1(tt, lexeme, 0);
	MSG(tok1);
};
void testScannerClassWithBadInput()
{
	TEST("ScannerClass with bad input.");
	ScannerClass scanner2("basic_test_bad.txt");
	TokenClass token2;
	while(token2.GetTokenType() != ENDFILE_TOKEN)
	{
		token2 = scanner2.GetNextToken();
		MSG(token2);
	};
}
void testScannerClass()
{
	TEST("ScannerClass with basic input.");
	ScannerClass scanner("basic_test.txt");
	TokenClass token;
	while(token.GetTokenType() != ENDFILE_TOKEN)
	{
		token = scanner.GetNextToken();
		MSG(token);
	};

	//testScannerClassWithBadInput();
};

int main()
{
	testTokenClass();
	testScannerClass();	
	system("pause");
	return 0;
};
