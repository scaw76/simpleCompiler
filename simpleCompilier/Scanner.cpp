#include <fstream>
#include <iostream>
#include <string>
#include "Scanner.h"
#include "Token.h"
#include "StateMachine.h"
#include "Debug.h"


ScannerClass::ScannerClass(const std::string filename)
	:mFin(filename),mLineNumber(1)
{
	MSG("Initializing ScannerClass object");
	if(!mFin){
		ERROR("ScannerClass: Error opening file!");
		system("pause");
		exit(0);
	}
};

ScannerClass::~ScannerClass(){
	mFin.close();
};

int ScannerClass::GetLineNumber()
{
	return mLineNumber;
};

TokenClass ScannerClass::GetNextToken()
{
	StateMachineClass myStateMachine;

	MachineState state;
	TokenType type;
	std::string lexeme;
	char c;
	do
	{
		c = mFin.get();
		state = myStateMachine.UpdateState(c,type);
		if( c=='\n'){
			mLineNumber ++;
			MSG("Linenumber: "<<mLineNumber);
		};
		lexeme += c;		
		
	}
	while(state != CANTMOVE_STATE);
	if(type == BAD_TOKEN)
	{
		ERROR("Bad token from character: "<< c );
		system("pause");
		exit(0);
	};
	// put c back
	mFin.unget(); 
	
	// remove c from lexeme
	lexeme = lexeme.substr(0, lexeme.size()-1); 

	TokenClass token(type, lexeme);
	return token;	
};