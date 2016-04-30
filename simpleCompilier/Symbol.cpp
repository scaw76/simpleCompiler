#include "Symbol.h"
#include "Debug.h"
#include <iostream>


SymbolTableClass::SymbolTableClass()
{};
SymbolTableClass::~SymbolTableClass()
{};
// does symbol exists
bool SymbolTableClass::Exists(std::string s)
{
	int index = mScoping[mScoping.size()-1];
	//MSG(index);
	for(std::vector<Variable>::reverse_iterator it = mSymbolTable.rbegin()+index; it != mSymbolTable.rend(); it++)
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
	//MSG("Symbol "<<s<<" added to table");	
};
// get value from symbol in table
int SymbolTableClass::GetValue(std::string s)
{
	for(std::vector<Variable>::reverse_iterator it = mSymbolTable.rbegin(); it != mSymbolTable.rend(); it++)
	{
		if(s.compare(it->mLabel) == 0)
		{
			int x = it->mValue;
			return x;
		};
	};
	VaribleNonExistent(s);
	return -1;
};
// set value for symbol in table
void SymbolTableClass::SetValue(std::string s, int v)
{
	for(std::vector<Variable>::reverse_iterator it = mSymbolTable.rbegin(); it != mSymbolTable.rend(); it++)
	{
		if(s.compare(it->mLabel) == 0)
		{
			it->mValue = v;
			return;
		};
	}
	VaribleNonExistent(s);
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
// push scope: records how many variables you have right now
void SymbolTableClass::PushScope()
{
	mScoping.push_back(mSymbolTable.size());
};
// pop scope
void SymbolTableClass::PopScope()
{
	int index = mScoping[mScoping.size()-1];

	while(mSymbolTable.size()>index)
	{
		mSymbolTable.pop_back();
	}
	mScoping.pop_back();
	//mSymbolTable = sub(&mSymbolTable.begin,&mSymbolTable.begin+index);
	
};
// nonexistant symbol print message and quit
void SymbolTableClass::VaribleNonExistent(std::string s)
{
	ERROR("Symbol: Error variable: "<<s<<" does not exist!");
	system("pause");
	exit(0);
}

