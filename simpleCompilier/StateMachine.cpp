#include <iostream>
#include "StateMachine.h"


StateMachineClass::StateMachineClass()
{
	std::cout<<"made state class succesfully"<<std::endl;
	mCurrentState = START_STATE;
	// initialize legal moves
	for(int i =0; i<LAST_STATE; i++)
	{
		for(int j= 0; j<LAST_CHAR; j++)
		{
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}
	
	// Define legal moves
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;

	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;

	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;

	//etc
	
	// Initialized corresponding token types
	for(int i = 0; i <LAST_STATE; i++)
	{
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}

	// Reset end states
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;	
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;

	// etc
};

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType)
{
	CharacterType charType = BAD_CHAR;

	if(isdigit(currentCharacter))
		charType = DIGIT_CHAR;
	if(isalpha(currentCharacter))
		charType = LETTER_CHAR;
	if(isspace(currentCharacter))
		charType = WHITESPACE_CHAR;
	if(currentCharacter=='+')
		charType = PLUS_CHAR;

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];

	return mCurrentState;
};
