#include "Symbol.h"
#include "Debug.h"
#include <iostream>


SymbolTableClass::SymbolTableClass()
{};
// does symbol exists
bool SymbolTableClass::Exists(std::string s)
{
	for(std::vector<Variable>::iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); it++)
	{
		if(s.compare(it->mLabel) == 0)
		{
			return true;
		};
	};
	return false;
};
// add symbol to table
void SymbolTableClass::AddEntry(std::string s)
{
	if(Exists(s))
	{
		ERROR("Symbol "<<s<<" already exists");
		system("pause");
		exit(0);
	}
	Variable v;
	v.mLabel = s;
	mSymbolTable.push_back(v);
	
};
// get value from symbol in table
int SymbolTableClass::GetValue(std::string s)
{
	for(std::vector<Variable>::iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); it++)
	{
		if(s.compare(it->mLabel) == 0)
		{
			return it->mValue;
		};
	};
	VaribleNonExistent();
};
// set value for symbol in table
void SymbolTableClass::SetValue(std::string s, int v)
{
	for(std::vector<Variable>::iterator it = mSymbolTable.begin(); it != mSymbolTable.end(); it++)
	{
		if(s.compare(it->mLabel) == 0)
		{
			it->mValue = v;
			return;
		};
	}
	VaribleNonExistent();
};
// get index of symbol in table
int SymbolTableClass::GetIndex(std::string s)
{
	int i = 0;
	for( std::vector<Variable>::iterator it = mSymbolTable.begin(); it != mSymbolTable.end();  it++)
	{
		i++;
		if(s.compare(it->mLabel) == 0)
		{
			return i-1;
		};
	}
	return -1;
}
// get count of symbols in table
int SymbolTableClass::GetCount()
{
	return mSymbolTable.size();
}
// if nonexistant symbol print message and quit
void SymbolTableClass::VaribleNonExistent()
{
	ERROR("Symbol: Error variable does not exist!");
	system("pause");
	exit(0);
}

