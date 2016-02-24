#include "Symbol.h"
#include <iostream>


SymbolTableClass::SymbolTableClass()
{

};
bool SymbolTableClass::Exists(std::string s)
{
	for(std::vector<Variable>::iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); it++)
	{
		if((it->mLabel) == s)
		{
			return true;
		}
	}
	return false;
};
void SymbolTableClass::AddEntry(std::string s)
{

};
int SymbolTableClass::GetValue(std::string s)
{
	return 0;
};
void SymbolTableClass::SetValue(std::string s)
{

};
int SymbolTableClass::GetIndex(std::string s)
{
	return 0;
};
int SymbolTableClass::GetCount()
{
	return 0;
};