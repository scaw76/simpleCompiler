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

	mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;

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
	// < > <= >= << 
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;

	mLegalMoves[LESS_STATE][ASSIGNMENT_CHAR] = LESSEQUAL_STATE;
	mLegalMoves[GREATER_STATE][ASSIGNMENT_CHAR] = GREATEREQUAL_STATE;
	
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	
	// = == ! !=
	mLegalMoves[START_STATE][ASSIGNMENT_CHAR] = ASSIGNMENT_STATE;
	mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = EQUAL_STATE;
	
	mLegalMoves[START_STATE][NEGATE_CHAR] = NEGATE_STATE;
	mLegalMoves[NEGATE_STATE][ASSIGNMENT_CHAR] = NOTEQUAL_STATE;

	// && ||
	mLegalMoves[START_STATE][AMPERSAND_CHAR] = AMPERSAND_STATE;
	mLegalMoves[IDENTIFIER_STATE][AMPERSAND_CHAR] = AMPERSAND_STATE;
	mLegalMoves[INTEGER_STATE][AMPERSAND_CHAR] = AMPERSAND_STATE;
	mLegalMoves[RPAREN_STATE][AMPERSAND_CHAR] = AMPERSAND_STATE;
	mLegalMoves[AMPERSAND_STATE][AMPERSAND_CHAR] = AND_STATE;

	mLegalMoves[AND_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[AND_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[AND_STATE][LETTER_CHAR] = IDENTIFIER_STATE;

	mLegalMoves[START_STATE][PIPE_CHAR] = PIPE_STATE;
	mLegalMoves[IDENTIFIER_STATE][PIPE_CHAR] = PIPE_STATE;
	mLegalMoves[INTEGER_STATE][PIPE_CHAR] = PIPE_STATE;
	mLegalMoves[RPAREN_STATE][PIPE_CHAR] = PIPE_STATE;
	mLegalMoves[PIPE_STATE][PIPE_CHAR] = OR_STATE;

	mLegalMoves[OR_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[OR_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[OR_STATE][LETTER_CHAR] = IDENTIFIER_STATE;

	// eof
	mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	
	// /* */ 
	
	// Initialize all BLOCKCOMMENT_STATE and ENDBLOCKCOMMENT_STATE
	for(int b= 0; b<LAST_CHAR; b++)
	{
		mLegalMoves[BLOCKCOMMENT_STATE][b] = BLOCKCOMMENT_STATE;
		mLegalMoves[ENDBLOCKCOMMENT_STATE][b] = BLOCKCOMMENT_STATE;
	}
	
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[DIVIDE_STATE][TIMES_CHAR] = BLOCKCOMMENT_STATE;

	mLegalMoves[BLOCKCOMMENT_STATE][TIMES_CHAR] = ENDBLOCKCOMMENT_STATE;
	mLegalMoves[BLOCKCOMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
	mLegalMoves[ENDBLOCKCOMMENT_STATE][TIMES_CHAR] = ENDBLOCKCOMMENT_STATE;
	mLegalMoves[ENDBLOCKCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;

	// //
	
	// Initialize all COMMENT_STATE and chars to COMMENT_STATE
	for(int cc= 0; cc<LAST_CHAR; cc++)
	{
		mLegalMoves[COMMENT_STATE][cc] = COMMENT_STATE;
	}
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = COMMENT_STATE;
	mLegalMoves[COMMENT_STATE][NEWLINE_CHAR] = START_STATE;
	mLegalMoves[COMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;

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
	mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;	
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;

	mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;

	mCorrespondingTokenTypes[ENDFILE_STATE] = ENDFILE_TOKEN;
	// etc
};

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType & correspondingTokenType)
{
	CharacterType charType = BAD_CHAR;

	if(isspace(currentCharacter))
		charType = WHITESPACE_CHAR;	
	if(currentCharacter=='\n')
		charType = NEWLINE_CHAR;	
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
	if(currentCharacter=='>')
		charType = GREATER_CHAR;
	if(currentCharacter=='=')
		charType = ASSIGNMENT_CHAR;
	if(currentCharacter=='!')
		charType = NEGATE_CHAR;
	if(currentCharacter=='&')
		charType = AMPERSAND_CHAR;
	if(currentCharacter=='|')
		charType = PIPE_CHAR;
	if(currentCharacter == EOF)
		charType = ENDFILE_CHAR;

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	
	mCurrentState = mLegalMoves[mCurrentState][charType];

	//MSG(correspondingTokenType<<" "<<mCurrentState);

	return mCurrentState;
};
