#pragma once
#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Symbol.h"
#include "Instructions.h"

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;

class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class IfStatementNode;
class WhileStatementNode;
class RepeatStatementNode;

// does not derive from node
class ExpressionNode;
class IntergerNode;
class IdentifierNode;

class BinaryOperatorNode;

class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;

class AndNode;
class OrNode;

// Node base class
class Node{
public:
	virtual void Interpret() = 0;
	virtual void Code(InstructionsClass & machine) = 0;
};

// Start Node
class StartNode : Node{
public:
	StartNode(ProgramNode * pn);
	~StartNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	ProgramNode * mProgramNode;
};

// Program Node
class ProgramNode : Node{
public:
	ProgramNode(BlockNode * bn);
	~ProgramNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	BlockNode * mBlockNode;
};
// Statement Node
class StatementNode : public Node{
public:
	StatementNode();
	virtual ~StatementNode();
};
// Block Node
class BlockNode : StatementNode {
public:
	BlockNode(StatementGroupNode * sg);
	~BlockNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	StatementGroupNode * mStatementGroupNode;
};
// Statement Group Node
class StatementGroupNode : Node {
public:
	StatementGroupNode();
	void AddStatement(StatementNode * sn);
	~StatementGroupNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	std::vector<StatementNode*> mStatementNodes;
};

// Declaration Statement Node
class DeclarationStatementNode : public StatementNode{
public:
	DeclarationStatementNode(IdentifierNode * id);
	~DeclarationStatementNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	IdentifierNode * mIdentifierNode;
};
// Assignment Statement Node
class AssignmentStatementNode : public StatementNode{
public:
	AssignmentStatementNode(IdentifierNode * id, ExpressionNode *en);
	~AssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	IdentifierNode * mIdentifierNode;
	ExpressionNode * mExpressionNode;
};
// Cout Statement Node
class CoutStatementNode : public StatementNode{
public:
	CoutStatementNode(ExpressionNode * en);
	~CoutStatementNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	ExpressionNode * mExpressionNode;
};
// If
class IfStatementNode : public StatementNode{
public:
	IfStatementNode(ExpressionNode* en, StatementGroupNode *sg);
	~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	ExpressionNode * mExpressionNode;
	StatementGroupNode * mStatementGroupNode;
};
//While
class WhileStatementNode : public StatementNode{
public:
	WhileStatementNode(ExpressionNode* en, StatementGroupNode *sg);
	~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	ExpressionNode * mExpressionNode;
	StatementGroupNode * mStatementGroupNode;
};
// Repeat
class RepeatStatementNode :public StatementNode{
public:
	RepeatStatementNode(ExpressionNode* en, StatementGroupNode *sg);
	~RepeatStatementNode();
	void Interpret();
	void Code(InstructionsClass & machine);
private:
	ExpressionNode * mExpressionNode;
	StatementGroupNode * mStatementGroupNode;
};

// DOES NODE DERIVED FROM NODE
// Expression Node
class ExpressionNode {
public:
	ExpressionNode();
	~ExpressionNode();
	virtual int Evaluate() = 0;
	virtual void CodeEvaluate(InstructionsClass &machine) = 0;
};
// Integer Node
class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int i);
	~IntegerNode();
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
private:
	int mInteger;
};
// Identifier Node /**** DOES NOT DESTROY POINTER
class IdentifierNode : public ExpressionNode{
public:
	IdentifierNode(std::string label, SymbolTableClass * st);
	~IdentifierNode();
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machine);
	std::string GetLabel();
private:
	std::string mLabel;
	SymbolTableClass * mSymbolTable;
};
// Binary Operator Node
class BinaryOperatorNode : public ExpressionNode{
public:
	BinaryOperatorNode(ExpressionNode * lhs, ExpressionNode * rhs);
	~BinaryOperatorNode();
protected:
	ExpressionNode * mRight;
	ExpressionNode * mLeft;
};
// Plus Node
class PlusNode : public BinaryOperatorNode{
public:
	PlusNode(ExpressionNode * lhs, ExpressionNode * rhs);
	~PlusNode();
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Minus Node
class MinusNode : public BinaryOperatorNode{
public:
	MinusNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Times Node
class TimesNode : public BinaryOperatorNode{
public:
	TimesNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Divide Node 
class DivideNode : public BinaryOperatorNode{
public:
	DivideNode(ExpressionNode *lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Less Node
class LessNode : public BinaryOperatorNode{
public:
	LessNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Less Equal Node
class LessEqualNode : public BinaryOperatorNode{
public:
	LessEqualNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Greater Node
class GreaterNode : public BinaryOperatorNode{
public:
	GreaterNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Greater Equal Node
class GreaterEqualNode : public BinaryOperatorNode{
public:
	GreaterEqualNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Equal Node
class EqualNode : public BinaryOperatorNode{
public:
	EqualNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Not Equal Node
class NotEqualNode : public BinaryOperatorNode{
public:
	NotEqualNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();	 
	 void CodeEvaluate(InstructionsClass &machine);
};
// And Node
class AndNode : public BinaryOperatorNode{
public:
	AndNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
// Or Node 
class OrNode : public BinaryOperatorNode{
public:
	OrNode(ExpressionNode * lhs, ExpressionNode * rhs);
	 int Evaluate();
	 void CodeEvaluate(InstructionsClass &machine);
};
#endif //_NODE_H_