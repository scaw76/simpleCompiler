#pragma once
#ifndef TOKEN
#define TOKEN

#include <iostream>

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, ENDL_TOKEN, BOOL_TOKEN, WHILE_TOKEN, IF_TOKEN, REPEAT_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUSEQUAL_TOKEN, MINUSEQUAL_TOKEN, TIMESEQUAL_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
	TIMES_TOKEN, DIVIDE_TOKEN,
	// 
	AND_TOKEN, OR_TOKEN,
	// Other Charaters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, BAD_TOKEN, ENDFILE_TOKEN
};

// TokenTypes and gTokenTypeNames must be kept in sync

const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "ENDL", "BOOL", "WHILE", "IF", "REPEAT",
	"LESS", "LESSEQUAL", "GREATER","GREATEREQUAL","EQUAL","NOTEQUAL",
	"INSERTION","ASSIGNMENT","PLUSEQUAL", "MINUSEQUAL","TIMESEQUAL","PLUS","MINUS","TIMES","DIVIDE",
	"AND", "OR",
	"SEMICOLON","LPAREN", "RPAREN","LCURLY","RCURLY",
	"IDENTIFIER","INTEGER",
	"BAD","ENDFILE"
};

class TokenClass {
public:
	TokenClass();
	TokenClass(TokenType type, const std::string & lexeme, int line);
	TokenType GetTokenType() const;
	std::string GetLexeme() const;
	int GetLineNumber() const;
	const std::string GetTypeString();
	const std::string GetTypeString(TokenType type);
	const std::string GetTokenTypeName() const;	
	
private:
	void CheckReserved();

	TokenType mType;
	std::string mLexeme;
	int mLineNumber;
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);

#endif // TOKEN