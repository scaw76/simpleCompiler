#pragma once
#ifndef _SCANNER_
#define	_SCANNER_
#include "Token.h"
#include <fstream>

class ScannerClass{

public:
	ScannerClass(const std::string filename);
	~ScannerClass();
	TokenClass GetNextToken();
	TokenClass PeekNextToken();
	int GetLineNumber();

private:
	std::ifstream mFin;
	int mLineNumber;
};


#endif // _SCANNER_