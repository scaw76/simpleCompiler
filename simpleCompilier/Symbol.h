#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include <string>
#include <vector>

class SymbolTableClass
{
	
public:
	SymbolTableClass();
	~SymbolTableClass();
	bool Exists(std::string s);
	void AddEntry(std::string s);
	int GetValue(std::string s);
	void SetValue(std::string s, int v);
	int GetIndex(std::string s);
	int GetCount();	
	// push scope: records how many variables you have right now
	void PushScope();
	// pop scope
	void PopScope();
private:
	void VaribleNonExistent(std::string s);
	struct Variable{
		std::string mLabel;
		int mValue;
	};
	std::vector<Variable> mSymbolTable;
	std::vector<int> mScoping;
};

#endif // _SYMBOL_H_