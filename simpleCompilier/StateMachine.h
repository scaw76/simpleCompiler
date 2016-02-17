#pragma once
#ifndef STATE_MACHINE
#define STATE_MACHINE

#include "Token.h"

enum MachineState{
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
	// etc
	LAST_STATE,
};

enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, BAD_CHAR,
	// etc
	LAST_CHAR
};

class StateMachineClass
{
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType & correspondingTokenType);
	MachineState mCurrentState;
private:
	
	// Legal moves matrix
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];
	TokenType mCorrespondingTokenTypes[LAST_STATE];
};


#endif // STATE_MACHINE