#include <iostream>
#include "StateMachine.h"
#include "Token.h"
#include "Debug.h"

StateMachineClass::StateMachineClass()
{
	//MSG("Initializing StateMachinClass");
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
	// ( ) { } ;
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	// * / - +
	mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	// < << <=
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	mLegalMoves[LESS_STATE][ASSIGNMENT_CHAR] = LESSEQUAL_STATE;
	// = ==
	mLegalMoves[START_STATE][ASSIGNMENT_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = EQUAL_STATE;

	mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	
	// /* */ 
	/*
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENT_STATE;

	mLegalMoves[BLOCKCOMMENT_STATE][WHITESPACE_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LETTER_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][DIGIT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LPAREN_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][RPAREN_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LCURLY_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][RCURLY_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][SEMICOLON_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][MINUS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][PLUS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][LESS_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][ASSIGNMENT_CHAR] = BLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][NEWLINE_CHAR] = BLOCKCOMMENT_STATE;


	mLegalMoves[BLOCKCOMMENT_STATE][TIMES_CHAR] = ENDBLOCKCOMMENT_STATE;
	mLegalMoves[ENDBLOCKCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;

	// //
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = COMMENT_STATE;

	mLegalMoves[COMMENT_STATE][WHITESPACE_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LETTER_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][DIGIT_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LPAREN_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][RPAREN_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LCURLY_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][RCURLY_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][SEMICOLON_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][MINUS_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][TIMES_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][DIVIDE_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][PLUS_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][LESS_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][ASSIGNMENT_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][NEWLINE_CHAR] = COMMENT_STATE;

	mLegalMoves[COMMENT_STATE][NEWLINE_CHAR] = START_STATE;
	*/

	//etc
	
	// Initialized corresponding token types
	for(int i = 0; i <LAST_STATE; i++)
	{
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}

	// Reset end states
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;	
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;

	mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;

	mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;	

	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;

	mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
	// etc
};

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType)
{
	CharacterType charType = BAD_CHAR;

	if(isspace(currentCharacter))
		charType = WHITESPACE_CHAR;	
	if(currentCharacter=='\n'){
		MSG("newline");
		//charType = NEWLINE_CHAR;
	}
	if(isalpha(currentCharacter))
		charType = LETTER_CHAR;	
	if(isdigit(currentCharacter))
		charType = DIGIT_CHAR;	
	if(currentCharacter=='(')
		charType = LPAREN_CHAR;
	if(currentCharacter==')')
		charType = RPAREN_CHAR;
	if(currentCharacter=='{')
		charType = LCURLY_CHAR;
	if(currentCharacter=='}')
		charType = RCURLY_CHAR;
	if(currentCharacter==';')
		charType = SEMICOLON_CHAR;
	if(currentCharacter=='*')
		charType = TIMES_CHAR;
	if(currentCharacter=='/')
		charType = DIVIDE_CHAR;
	if(currentCharacter=='-')
		charType = MINUS_CHAR;
	if(currentCharacter=='+')
		charType = PLUS_CHAR;
	if(currentCharacter=='<')
		charType = LESS_CHAR;
	if(currentCharacter=='=')
		charType = ASSIGNMENT_CHAR;
	if(currentCharacter == EOF)
		charType = ENDFILE_CHAR;

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	
	mCurrentState = mLegalMoves[mCurrentState][charType];

	//MSG(correspondingTokenType<<" "<<mCurrentState);

	return mCurrentState;
};
