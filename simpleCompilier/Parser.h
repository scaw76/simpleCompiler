#ifndef _PARSER_H_
#define _PARSER_H_

#include "Scanner.h"
#include "Symbol.h"


class ParserClass
{
public:
	ParserClass(ScannerClass * sc, SymbolTableClass * st);
	void Start();
private:
	ScannerClass * mScanner;
	SymbolTableClass *mSymbolTable;
};

#endif // _PARSER_H_

