#include <fstream>
#include <iostream>
#include "Scanner.h"
#include "Token.h"
#include "StateMachine.h"
#include <string>



ScannerClass::ScannerClass(const std::string filename)
	:mFin(filename)
{
	if(!mFin){
		std::cout<<"ScannerClass: Error opening file!"<<std::endl;
		system("pause");
		exit(0);
	}
};

ScannerClass::~ScannerClass(){
	mFin.close();
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
		//std::cout<< c <<std::endl;
		state = myStateMachine.UpdateState(c,type);
		lexeme += c;
	}
	while(state != CANTMOVE_STATE);
	if(type == BAD_TOKEN)
	{
		std::cout<<"Bad token from character: "<< c <<std::endl;
		system("pause");
		exit(0);
	}
	// put c back
	mFin.unget(); 
	// remove c from lexeme
	lexeme = lexeme.substr(0, lexeme.size()-1); 
	TokenClass token(type, lexeme);
	return token;	
};


	