#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include <string>
#include <vector>

class SymbolTableClass
{
public:
	SymbolTableClass();
	bool Exists(std::string s);
	void AddEntry(std::string s);
	int GetValue(std::string s);
	void SetValue(std::string s);
	int GetIndex(std::string s);
	int GetCount();

std::struct Variable{
	std::string mLabel;
	int mValue;
};
private:
	std::vector<Variable> mSymbolTable;
}

#endif // _SYMBOL_H_