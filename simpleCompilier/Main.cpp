#include "Debug.h"
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include <iostream>

/* Commented out tests are fail and quit tests*/
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
		//MSG(token);
	};
	//testScannerClassWithBadInput();
};
void testSymbolTable()
{
	SymbolTableClass Table;
	//bool t1 = Table.Exists("");
	std::string e1 = "entry1";
	std::string e2 = "babby";
	bool t2 = Table.Exists(e1);
	
	Table.AddEntry(e1);
	Table.AddEntry(e2);
	bool t3 = Table.Exists(e1);
	Table.SetValue(e1, 5);
	
	//int t4 = Table.GetValue(e1);
	int t5 = Table.GetValue(e1);
	int t6 = Table.GetIndex(e2);
	
	int t7 = Table.GetCount();
	/*
	MSG("0= "<<t2);
	MSG("1= "<<t3);
	MSG("5= "<<t5);
	MSG("1= "<<t6);
	MSG("2= "<<t7);
	*/
	if(!t2 && t3 && (t5==5) && (t6 ==1)&& (t7 == 2))
	{
		MSG("Passed symbol table tests!");
	}
}

void testNodeClasses()
{
	x = new IntegerNode(20);
	y = new IntegerNode(4);


}

int main()
{
	testTokenClass();
	testScannerClass();	
	testSymbolTable();
	testNodeClasses();
	system("pause");
	return 0;
};
