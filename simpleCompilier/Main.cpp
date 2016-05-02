#include "Debug.h"
//#include "Test.h"
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"
#include <iostream>
//#include <array>

/* Commented out tests are fail and quit tests*/
/*
void testTokenClass()
{
	std::string unit = "TokenClass Unit Test";
	TokenType tt = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass tok1(tt, lexeme, 0);
	UnitTest tc(unit);
	tc.AddTest(Test("Token mType set and get.", tt==tok1.GetTokenType()));
	tc.AddTest(Test("Token mLexeme set and get.", lexeme.compare(tok1.GetLexeme())==0));
	tc.AddTest(Test("Token mLine set and get.", tok1.GetLineNumber()==0));
	//MSG((tok1.GetTokenTypeName()));
	//MSG(lexeme.compare(tok1.GetTokenTypeName()));
	tc.AddTest(Test("Token GetTypeString no input", lexeme.compare(tok1.GetTokenTypeName())>0 ));
	//MSG(tok1.GetTypeString(INT_TOKEN));
	//MSG(tok1.GetTypeString(INT_TOKEN).compare("int"));
	tc.AddTest(Test("Token GetTypeString with input", tok1.GetTypeString(INT_TOKEN).compare("int")<0));

	//MSG(tok1);
	
	tc.Evaluate();
};

void testScannerClassWithBadInput()
{
	TEST("ScannerClass with bad input.");
	ScannerClass scanner2("basic_test_bad.txt");
	TokenClass token2;
	while(token2.GetTokenType() != ENDFILE_TOKEN)
	{
		token2 = scanner2.GetNextToken();
		//MSG(token2);
	};
}
void testScannerClass()
{
	TEST("ScannerClass");
	ScannerClass scanner("test.txt");
	TokenClass token;
	while(token.GetTokenType() != ENDFILE_TOKEN)
	{
		TokenClass t = scanner.PeekNextToken();
		//MSG("Peeked at "<<t);
		token = scanner.GetNextToken();
		//MSG("Got "<<token);
	};
	// test bad input
	//testScannerClassWithBadInput();
};
void testSymbolTable()
{
	std::string unit = "SymbolTableClass Unit Test";
	SymbolTableClass *Table = new SymbolTableClass;
	UnitTest tc(unit);
	
	std::string e1 = "entry1";
	// test nonexistant variable
	// tc.AddTest(Test("Table set and get value.",(Table->GetValue(e1) == 5) ));
	std::string e2 = "babby";
	// Fail case
	tc.AddTest(Test("Table entry exists: Faile case. ",!(Table->Exists(e1)) ));

	Table->AddEntry(e1);
	Table->AddEntry(e2);
	tc.AddTest(Test("Table entry exists.",(Table->Exists(e1)) ));

	Table->SetValue(e1,5);
	tc.AddTest(Test("Table set and get value.",(Table->GetValue(e1) == 5) ));
	tc.AddTest(Test("Table get index.",Table->GetIndex(e2) == 1 ));
	
	tc.AddTest(Test("Table get count.",Table->GetCount() == 2 ));
	
	tc.Evaluate();
}

void testNodeClasses()
{
	std::string unit = "NodeClasses Unit Test";
	SymbolTableClass *Table = new SymbolTableClass;

	UnitTest nc(unit);

	int r = 20;
	int l = 4;
	IntegerNode *rhs = new IntegerNode(r);
	IntegerNode *lhs = new IntegerNode(l);

	nc.AddTest(Test("IntegerNode.", (rhs->Evaluate()==20) ));
	IdentifierNode *sum = new IdentifierNode("sum", Table);
	DeclarationStatementNode *dn = new DeclarationStatementNode(sum);
	dn->Interpret();
	nc.AddTest(Test("DeclarationStatementNode interpreted IdentifierNode adding to table.", Table->Exists("sum") ));
	// +
	PlusNode *pn =  new PlusNode(lhs, rhs);
	nc.AddTest(Test("AddNode.",( pn->Evaluate()==24) ));
	// Assignment and Cout Nodes need their own pointers to expression nodes for their destructors to work properly
	AssignmentStatementNode *an = new AssignmentStatementNode(new IdentifierNode("sum", Table),new PlusNode(lhs, rhs));
	an->Interpret();

	nc.AddTest(Test("AssignmentStatementNode interpreted Assignmentnode seting value in table", (Table->GetValue("sum")==24) ));
	CoutStatementNode *cn = new CoutStatementNode();
	cn->AddExpressionNode(new IdentifierNode("sum", Table));
	MSG("Next line should be 24");
	cn->Interpret();

	StatementGroupNode * sg = new StatementGroupNode();	
	sg->AddStatement(dn);
	sg->AddStatement(an);
	sg->AddStatement(cn);

	BlockNode *bn = new BlockNode(sg, Table);
	ProgramNode * PN = new ProgramNode(bn);
	
	StartNode * sn = new StartNode(PN);
	
	// undo comments in Node.cpp to see working chain
	delete sn;
	delete rhs;
	delete lhs;
	delete Table;
	/*
	
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
	/*
	nc.Evaluate();


}

void TestParser()
{
	TEST("ParserClass.");
	ParserClass *Parser = new ParserClass(new ScannerClass("test_plus_minus_assignment.txt"),new SymbolTableClass);
	
	StartNode *ns = Parser->Start();
	delete ns;
	delete Parser;
};
*/
void TestInterpreter(std::string filename){
	//TEST("Intrepreter.");
	ParserClass *Parser = new ParserClass(new ScannerClass(filename),new SymbolTableClass);
	StartNode * root = Parser->Start();
	root->Interpret();
	delete root;
	delete Parser;
};

void MachineCode(std::string filename){
	//TEST("InstructionsClass.");
	ParserClass *Parser = new ParserClass(new ScannerClass(filename),new SymbolTableClass);
	StartNode * root = Parser->Start();

	InstructionsClass instructions= InstructionsClass();
	root->Code(instructions);

	instructions.PrintAllMachineCodes();
	instructions.Finish();
	instructions.Execute();
	
	delete root;
	delete Parser;
}
void TestInstructionClass(){
	InstructionsClass instructions= InstructionsClass();
	/*
	instructions.PushValue(5);
	instructions.PushValue(3);
	instructions.PopPopAddPush();
	instructions.PopAndWrite();
	*/
	instructions.PrintAllMachineCodes();

	instructions.Finish();
	instructions.Execute();
};
int main()
{
	//testTokenClass();
	//testScannerClass();		
	//testSymbolTable();
	//testNodeClasses();
	//TestParser();
	//TestInterpreter("test.txt");
	//TestInterpreter("test_basic.txt");
	//TestInterpreter("test_cout.txt");
	TestInterpreter("test_scoping.txt");
	//TestInstructionClass();
	//MachineCode("test.txt");
	//MachineCode("test_cout.txt");
	//MachineCode("test_plus_minus_assignment.txt");
	//MachineCode("test_scoping.txt");

	//system("pause");
	
	return 0;
};
