#pragma once
#ifndef TOKEN
#define TOKEN

#include <iostream>

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
	TIMES_TOKEN, DIVIDE_TOKEN,
	// Other Charaters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN, RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN, BAD_TOKEN, ENDFILE_TOKEN
};

// TokenTypes and gTokenTypeNames must be kept in sync

const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT",
	"LESS", "LESSEQUAL", "GREATER","GREATEREQUAL","EQUAL","NOTEQUAL",
	"INSERTION","ASSIGNMENT","PLUS","MINUS","TIMES","DIVIDE",
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
	const std::string & GetTokenTypeName() const;	
	void CheckReserved();
private:
	TokenType mType;
	std::string mLexeme;
	int mLineNumber;
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc);

#endif // TOKEN