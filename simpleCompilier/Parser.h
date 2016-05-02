#ifndef _PARSER_H_
#define _PARSER_H_

#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"


class ParserClass
{
public:
	ParserClass(ScannerClass * sc, SymbolTableClass * st);
	~ParserClass();
	StartNode * Start();
private:
	TokenClass Match(TokenType expectedType);
	ProgramNode * Program();
	StatementNode * Block();
	StatementGroupNode * StatementGroup();
	StatementNode * Statement();


	StatementNode* DeclarationStatement(TokenType tt);
	StatementNode * AssignmentStatement();
	CoutStatementNode * CoutStatement();
	IfStatementNode * IfStatement();
	WhileStatementNode * WhileStatement();
	WhileStatementNode * DoWhileStatement();
	RepeatStatementNode *RepeatStatement();

	ExpressionNode * Expression();
	ExpressionNode * And();
	ExpressionNode * Or();
	ExpressionNode * Relational();
	ExpressionNode * PlusMinus();
	ExpressionNode * TimesDivide();
	ExpressionNode *  Factor();

	IdentifierNode * Identifier();
	IntegerNode * Integer();
	
	ScannerClass * mScanner;
	SymbolTableClass *mSymbolTable;
};

#endif // _PARSER_H_

