#pragma once
#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "Symbol.h"

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;

// does not derive from node
class ExpressionNode;
class IntergerNode;
class IdentifierNode;

class BinaryOperatorNode;
class PlusNode;



// Node base class
class Node{
public:
	~Node();
};
// Start Node
class StartNode : Node{
public:
	StartNode(ProgramNode * pn);
	~StartNode();
private:
	ProgramNode * mProgramNode;
};
// Program Node
class ProgramNode : Node{
public:
	ProgramNode(BlockNode * bn);
	~ProgramNode();
private:
	BlockNode * mBlockNode;
};
// Block Node
class BlockNode : Node {
public:
	BlockNode(StatementGroupNode * sg);
	~BlockNode();
private:
	StatementGroupNode * mStatementGroupNode;
};
// Statement Group Node
class StatementGroupNode : Node {
public:
	StatementGroupNode();
	void AddStatement(StatementNode * sn);
	~StatementGroupNode();
private:
	std::vector<StatementNode*> mStatementNodes;
};
// Statement Node
class StatementNode : Node{
public:
	StatementNode();
	~StatementNode();
};
// Declaration Statement Node
class DeclarationStatementNode : StatementNode{
public:
	DeclarationStatementNode(IdentifierNode * id);
	~DeclarationStatementNode();
private:
	IdentifierNode * mIdentifierNode;
};
// Assignment Statement Node
class AssignmentStatementNode : StatementNode{
public:
	AssignmentStatementNode(IdentifierNode * id, ExpressionNode *en);
	~AssignmentStatementNode();
private:
	IdentifierNode * mIdentifierNode;
	ExpressionNode * mExpressionNode;
};
// Cout Statement Node
class CoutStatementNode : StatementNode{
public:
	CoutStatementNode(ExpressionNode * en);
	~CoutStatementNode();
private:
	ExpressionNode * mExpressionNode;
};
// DOES NODE DERIVED FROM NODE
// Expression Node
class ExpressionNode {
public:
	virtual int Evaluate() = 0;
	~ExpressionNode();
};
// Integer Node
class IntegerNode : ExpressionNode {
public:
	IntegerNode(int i);
	int Evaluate();
private:
	int mInteger;
};
// Identifier Node /**** DOES NOT DESTROY POINTER
class IdentifierNode : ExpressionNode{
public:
	IdentifierNode(std::string label, SymbolTableClass * st);
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	int Evaluate();
private:
	std::string mLabel;
	SymbolTableClass * mSymbolTable;
};
// Binary Operator Node
class BinaryOperatorNode : public ExpressionNode{
public:
	BinaryOperatorNode(ExpressionNode * rhs, ExpressionNode * lhs);
	~BinaryOperatorNode();
protected:
	ExpressionNode * mRight;
	ExpressionNode * mLeft;
};
// Plus Node
class PlusNode : BinaryOperatorNode{
public:
	PlusNode(ExpressionNode * rhs, ExpressionNode * lhs);
	int Evaluate();
};


#endif //_NODE_H_