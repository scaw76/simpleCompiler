#include "Token.h"
#include "Debug.h"
#include <iostream>
#include <string>

TokenClass::TokenClass()
{
	//MSG("Initializing empty TokenClass");
};
TokenClass::TokenClass(TokenType type, const std::string & lexeme, int line)
{
	//MSG("Initializing TokenClass");
	mType = type;
	mLexeme = lexeme;
	mLineNumber = line;
};

TokenType TokenClass::GetTokenType() const 
{
	return mType;
};

std::string TokenClass::GetLexeme() const
{
	return mLexeme;
};
int TokenClass::GetLineNumber() const
{
	return mLineNumber;
};

const std::string & TokenClass::GetTokenTypeName() const 
{
	return gTokenTypeNames[mType];
};

void TokenClass::CheckReserved()
{
	if(mLexeme.compare("void")==0)
	{
		mType = VOID_TOKEN;
	}
	if(mLexeme.compare("main")==0)
	{
		mType = MAIN_TOKEN;
	}
	if(mLexeme.compare("int")==0)
	{
		mType = INT_TOKEN;
	}
	if(mLexeme.compare("cout")==0)
	{
		mType = COUT_TOKEN;
	}
};

std::ostream & operator<<(std::ostream & out, const TokenClass & tc)
{
	TokenType type= tc.GetTokenType();
	std::string name= tc.GetTokenTypeName();
	std::string lexeme = tc.GetLexeme();
	int line = tc.GetLineNumber();

	out<<"Tokeyn: type: " <<type<<" name: "<<name<<" lexeme: "<<lexeme<<" LineNumber:"<<line;

	return out;
};
