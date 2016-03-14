#include "Node.h"


Node::~Node(){};
// StartNode
StartNode::StartNode(ProgramNode * pn)
{
	mProgramNode = pn;
};
StartNode::~StartNode()
{
	delete mProgramNode;
};
// Program Node
ProgramNode::ProgramNode(BlockNode * bn)
{
	mBlockNode = bn;
};
ProgramNode::~ProgramNode()
{
	delete mBlockNode;
};
// Block Node
BlockNode::BlockNode(StatementGroupNode * sg)
{
	mStatementGroupNode = sg;
};
BlockNode::~BlockNode()
{
	delete mStatementGroupNode;
};
// Statement Group Node
StatementGroupNode::StatementGroupNode()
{};
StatementGroupNode::~StatementGroupNode()
{
	for(std::vector<StatementNode*>::iterator it = mStatementNodes.begin(); it != mStatementNodes.end(); it++)
	{
		delete *it;
	}
};
void StatementGroupNode::AddStatement(StatementNode * sn)
{
	mStatementNodes.push_back(sn);
};
// Statement Node
StatementNode::StatementNode(){};
StatementNode::~StatementNode(){};
// Declaration Statement Node
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode * id)
{
	mIdentifierNode = id;
};
DeclarationStatementNode::~DeclarationStatementNode()
{
	delete mIdentifierNode;
};
// Assignment Statement Node
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode * id, ExpressionNode *en)
{
	mIdentifierNode = id;
	mExpressionNode = en;
};
AssignmentStatementNode::~AssignmentStatementNode()
{
	delete mIdentifierNode;
	delete mExpressionNode;
};
// Cout Statement Node
CoutStatementNode::CoutStatementNode(ExpressionNode * en)
{
	mExpressionNode = en;
};
CoutStatementNode::~CoutStatementNode()
{
	delete mExpressionNode;
};
// Expression Node
ExpressionNode::~ExpressionNode(){};
// Integer Node
IntegerNode::IntegerNode(int i)
{
	mInteger = i;
};
int IntegerNode::Evaluate()
{
	return mInteger;
};
// Identifier Node
IdentifierNode::IdentifierNode(std::string label, SymbolTableClass * st)
{
	mLabel = label;
	mSymbolTable = st;
};
void IdentifierNode::DeclareVariable()
{
	mSymbolTable->AddEntry(mLabel);
};
void IdentifierNode::SetValue(int v)
{
	mSymbolTable->SetValue(mLabel,v);
};
int IdentifierNode::GetIndex()
{
	return mSymbolTable->GetIndex(mLabel);
};
int IdentifierNode::Evaluate()
{
	return mSymbolTable->GetValue(mLabel);
};
// Binary Operator Node
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * rhs, ExpressionNode * lhs)
{
	mRight = rhs;
	mLeft = lhs;
};
BinaryOperatorNode::~BinaryOperatorNode()
{
	delete mRight;
	delete mLeft;
};
// Plus Node
PlusNode::PlusNode(ExpressionNode * rhs, ExpressionNode * lhs)
	: BinaryOperatorNode(rhs,lhs)
{};
int PlusNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return right + left;
};

