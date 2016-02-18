#pragma once
#ifndef STATE_MACHINE
#define STATE_MACHINE

#include "Token.h"

enum MachineState{
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE,
	LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE, SEMICOLON_STATE,
	TIMES_STATE, DIVIDE_STATE, MINUS_STATE, PLUS_STATE, 
	LESS_STATE, INSERTION_STATE, LESSEQUAL_STATE, ASSIGNMENT_STATE, EQUAL_STATE,
	ENDFILE_STATE,
	CANTMOVE_STATE,

	// etc
	LAST_STATE,
};

enum CharacterType {
	WHITESPACE_CHAR, LETTER_CHAR, DIGIT_CHAR,
	LPAREN_CHAR, RPAREN_CHAR, LCURLY_CHAR, RCURLY_CHAR, SEMICOLON_CHAR,
	TIMES_CHAR,	DIVIDE_CHAR, MINUS_CHAR, PLUS_CHAR,
	LESS_CHAR, ASSIGNMENT_CHAR,
	ENDFILE_CHAR,
	BAD_CHAR,
	// etc
	LAST_CHAR,
};

class StateMachineClass
{
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType & correspondingTokenType);
	
private:
	MachineState mCurrentState;
	// Legal moves matrix
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];
	TokenType mCorrespondingTokenTypes[LAST_STATE];
};


#endif // STATE_MACHINE