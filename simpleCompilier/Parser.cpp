#include "Parser.h"
#include "Debug.h"
#include "Token.h"

ParserClass::ParserClass(ScannerClass * sc, SymbolTableClass * st)
{
	mScanner = sc;
	mSymbolTable = st;
};
ParserClass::~ParserClass()
{
	delete mScanner;
	delete mSymbolTable;
};
StartNode * ParserClass::Start()
{
	ProgramNode *p = Program();
	Match(ENDFILE_TOKEN);
	StartNode * n = new StartNode(p);
	return n;	
};
ProgramNode * ParserClass::Program()
{
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode *b = Block();
	return new ProgramNode(b);
};
BlockNode * ParserClass::Block()
{
	Match(LCURLY_TOKEN);
	StatementGroupNode * s = StatementGroup();
	Match(RCURLY_TOKEN);
	Match(SEMICOLON_TOKEN);
	BlockNode * b = new BlockNode(s);
	return b;
};
StatementGroupNode * ParserClass::StatementGroup()
{
	StatementGroupNode * sg = new StatementGroupNode();	
	while(true)
	{
		StatementNode * sn = Statement();
		if(!sn)
			break;
		sg->AddStatement(sn);
	};

	return sg;
};
StatementNode * ParserClass::Statement()
{
	TokenClass currentToken = mScanner->PeekNextToken();
	TokenType tt = currentToken.GetTokenType();
	if(tt == INT_TOKEN || tt == BOOL_TOKEN)
	{
		return DeclarationStatement(tt);
	}
	else if(tt == IDENTIFIER_TOKEN )
	{
		return AssignmentStatement();
	}
	else if(tt == COUT_TOKEN)
	{
		return CoutStatement();
	}
	return NULL;
	
};
AssignmentStatementNode * ParserClass::AssignmentStatement()
{
	IdentifierNode * id = Identifier();
	TokenClass token = Match(ASSIGNMENT_TOKEN);
	ExpressionNode * ex = Expression();
	AssignmentStatementNode * a = new AssignmentStatementNode(id, ex);
	Match(SEMICOLON_TOKEN);
	return a;
};

DeclarationStatementNode* ParserClass::DeclarationStatement(TokenType tt)
{
	if(tt == INT_TOKEN)
	{
		TokenClass token = Match(INT_TOKEN);
	}
	else if( tt == BOOL_TOKEN)
	{
		TokenClass token = Match(BOOL_TOKEN);
	}
	IdentifierNode *id = Identifier();
	Match(SEMICOLON_TOKEN);
	return new DeclarationStatementNode(id);
};
CoutStatementNode * ParserClass::CoutStatement()
{
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode * ex = Expression();	
	Match(SEMICOLON_TOKEN);
	return new CoutStatementNode(ex);
};
IdentifierNode * ParserClass::Identifier()
{
	TokenClass token = Match(IDENTIFIER_TOKEN);
	IdentifierNode * id = new IdentifierNode(token.GetLexeme(),mSymbolTable);
	//MSG(id->GetLabel());
	return id;
};
IntegerNode * ParserClass::Integer()
{
	TokenClass token = Match(INTEGER_TOKEN);
	return new IntegerNode(stoi(token.GetLexeme()));
};


TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mScanner->GetNextToken();
	TokenType tt = currentToken.GetTokenType();
	if(currentToken.GetTokenType() != expectedType){
		std::cerr<<"Error in ParserClass::Match. "<<std::endl;
		std::cerr<<"Expected token type "<<
			currentToken.GetTypeString(expectedType)<<
			std::endl;
		exit(1);
	}

	MSG("\tSuccessfully match Token Type: "<<
		currentToken.GetTypeString()<<". Lexeme: \""<<
		currentToken.GetLexeme()<<"\"");

	return currentToken;
};

ExpressionNode * ParserClass::Expression()
{
	ExpressionNode *  current = PlusMinus();
	TokenClass currentToken = mScanner->PeekNextToken();
	TokenType tt = currentToken.GetTokenType();
	if(tt == LESS_TOKEN 
		||tt == LESSEQUAL_TOKEN 
		||tt == GREATER_TOKEN
		||tt == GREATEREQUAL_TOKEN
		||tt == EQUAL_TOKEN
		||tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		if(tt == LESS_TOKEN )
			current = new LessNode(current,PlusMinus());
		else if(tt == LESSEQUAL_TOKEN )
			current = new LessEqualNode(current,PlusMinus());
		else if(tt == GREATER_TOKEN )
			current = new GreaterNode(current,PlusMinus());
		else if(tt == GREATEREQUAL_TOKEN )
			current = new GreaterEqualNode(current,PlusMinus());
		else if(tt == EQUAL_TOKEN )
			current = new EqualNode(current,PlusMinus());
		else if(tt == NOTEQUAL_TOKEN )
			current = new NotEqualNode(current,PlusMinus());
	}
	return current;
};
ExpressionNode * ParserClass::PlusMinus()
{
	ExpressionNode * current = TimesDivide();
	while(true){
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == PLUS_TOKEN)
		{
			Match(PLUS_TOKEN);
			current = new PlusNode(current,TimesDivide());
		}
		else if(tt == MINUS_TOKEN)
		{
			Match(MINUS_TOKEN);
			current = new MinusNode(current,TimesDivide());
		}
		else
		{
			break;
		}
		
	}
	return current;
};
ExpressionNode * ParserClass::TimesDivide()
{
	ExpressionNode * current = Factor();
	while(true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if(tt == TIMES_TOKEN)
		{
			Match(tt);
			current = new TimesNode(current,Factor());
		}
		else if(tt == DIVIDE_TOKEN)
		{
			Match(tt);
			current = new DivideNode(current,Factor());
		}
		else
		{
			break;
		}
	}
	return current;
};
ExpressionNode *  ParserClass::Factor()
{
	TokenClass currentToken = mScanner->PeekNextToken();
	TokenType tt = currentToken.GetTokenType();
	if(tt == IDENTIFIER_TOKEN)
	{
		return Identifier();
	}
	else if(tt == INTEGER_TOKEN)
	{
		return Integer();
	}
	else if(tt == LPAREN_TOKEN)
	{
		Match(LPAREN_TOKEN);
		ExpressionNode *  p =  Expression();
		Match(RPAREN_TOKEN);
		return p;
	}
};