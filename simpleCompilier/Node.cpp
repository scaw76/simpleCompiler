#include <iostream>
#include "Node.h"
#include "Debug.h"

Node::Node(){};
Node::~Node(){ MSG("de-contruct Node"); };
// StartNode
StartNode::StartNode(ProgramNode * pn)
{
	mProgramNode = pn;
};
StartNode::~StartNode()
{
	MSG("de-contruct StartNode");
	delete mProgramNode;
};
// Program Node
ProgramNode::ProgramNode(BlockNode * bn)
{
	mBlockNode = bn;
};
ProgramNode::~ProgramNode()
{
	MSG("de-contruct ProgramNode");
	delete mBlockNode;
};
// Block Node
BlockNode::BlockNode(StatementGroupNode * sg)
	:StatementNode()
{
	mStatementGroupNode = sg;
};
BlockNode::~BlockNode()
{
	MSG("de-contruct BlockNode");
	delete mStatementGroupNode;
};
// Statement Group Node
StatementGroupNode::StatementGroupNode()
{};
StatementGroupNode::~StatementGroupNode()
{
	MSG("de-contruct StatementGroupNode");
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
StatementNode::StatementNode():Node(){};
StatementNode::~StatementNode(){ MSG("de-contruct StatementNode"); };
// Declaration Statement Node
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode * id)
{
	mIdentifierNode = id;
};
DeclarationStatementNode::~DeclarationStatementNode()
{
	MSG("de-contruct DeclarationStatementNode");
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
	MSG("de-contruct AssignmentStatementNode");

	delete mIdentifierNode;
	delete mExpressionNode;
};
ExpressionNode::ExpressionNode()
{};
ExpressionNode::~ExpressionNode()
{ MSG("de-contruct ExpressionNode"); };
// Cout Statement Node
CoutStatementNode::CoutStatementNode(ExpressionNode * en)
	:StatementNode()
{
	mExpressionNode = en;
};
CoutStatementNode::~CoutStatementNode()
{
	MSG("de-contruct CoutStatementNode");
	delete mExpressionNode;
};

// Integer Node
IntegerNode::IntegerNode(int i)
	:ExpressionNode()
{
	mInteger = i;
};
IntegerNode::~IntegerNode(){ MSG("de-contruct IntegerNode"); };
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
IdentifierNode::~IdentifierNode()
{
	MSG("de-contruct IdentifierNode");
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
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * lhs, ExpressionNode * rhs)
{
	mRight = rhs;
	mLeft = lhs;
};
BinaryOperatorNode::~BinaryOperatorNode()
{
	MSG("de-contruct BinaryOperatorNode"); 
	delete mRight;
	delete mLeft;
};
// Plus Node
PlusNode::PlusNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
PlusNode::~PlusNode()
{
	MSG("de-contruct PlusNode"); 
};
int PlusNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return left + right;
};
// Minus Node
MinusNode::MinusNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int MinusNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return left - right;
};
// Times Node
TimesNode::TimesNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int TimesNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return left * right;
};
// Divide Node
DivideNode::DivideNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int DivideNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return left / right;
};

// Less Node
LessNode::LessNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int LessNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return right < left;
};
// Less Equal Node
LessEqualNode::LessEqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int LessEqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return left <= right;
};
// Greater Node
GreaterNode::GreaterNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int GreaterNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return right > left;
};
// Greater Equal Node
GreaterEqualNode::GreaterEqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int GreaterEqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return right >= left;
};
// Equal Node
EqualNode::EqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int EqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return right == left;
};
// Not Equal Node
NotEqualNode::NotEqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
int NotEqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	return right != left;
};