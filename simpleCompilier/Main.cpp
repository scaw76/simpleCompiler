#include "Debug.h"
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"
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
	TokenClass t = scanner.PeekNextToken();
	MSG(t);
	while(token.GetTokenType() != ENDFILE_TOKEN)
	{
		token = scanner.GetNextToken();
		MSG(token);
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
	int r = 20;
	int l = 4;

	std::string label = "myLabel";
	/*
	BlockNode;
	StatementGroupNode;
	StatementNode;
	DeclarationStatementNode;
	AssignmentStatementNode;
	CoutStatementNode;
	*/

	IntegerNode *rhs = new IntegerNode(r);
	IntegerNode *lhs = new IntegerNode(l);
	/*
	PlusNode *pn =  new PlusNode(lhs, rhs);
	MinusNode *mn = new MinusNode(lhs, rhs);
	
	TimesNode *tm = new TimesNode(lhs, rhs);
	DivideNode *dn = new DivideNode(lhs, rhs);

	LessNode *ln =  new LessNode(lhs, rhs);
	LessEqualNode *len = new LessEqualNode(lhs, rhs);

	GreaterNode *gn = new GreaterNode(lhs, rhs);
	GreaterEqualNode *gen = new GreaterEqualNode(lhs, rhs);

	EqualNode *en = new EqualNode(lhs,rhs);
	NotEqualNode *nen = new NotEqualNode(lhs, rhs);

	
	*/
	SymbolTableClass *Table = new SymbolTableClass;

	IdentifierNode *id = new IdentifierNode(label, Table);

	CoutStatementNode *csn = new CoutStatementNode(rhs);
	AssignmentStatementNode *asn = new AssignmentStatementNode(id, rhs);
	DeclarationStatementNode *dsn = new DeclarationStatementNode(id);

	StatementGroupNode * sg = new StatementGroupNode();	
	sg->AddStatement(csn);
	sg->AddStatement(asn);
	sg->AddStatement(dsn);

	BlockNode *bn = new BlockNode(sg);
	ProgramNode * PN = new ProgramNode(bn);
	
	StartNode * sn = new StartNode(PN);
	
	delete sn;
	delete rhs;
	delete lhs;
}

void TestParser()
{
	TEST("ParserClass with basic input.");
	ScannerClass *Scanner = new ScannerClass("basic_test.txt");
	SymbolTableClass *Table = new SymbolTableClass;

	ParserClass Parser(Scanner,Table);
	//StartNode * sn = 
	Parser.Start();

};

int main()
{
	testTokenClass();
	testScannerClass();	
	testSymbolTable();
	testNodeClasses();
	TestParser();
	system("pause");
	return 0;
};
