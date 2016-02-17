#pragma once
#ifndef SCANNER
#define	SCANNER
#include "Token.h"
#include <fstream>

class ScannerClass{

public:
	ScannerClass(const std::string filename);
	~ScannerClass();
	TokenClass GetNextToken();

private:
	std::ifstream mFin;
};


#endif // SCANNER