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
void StartNode::Interpret()
{
	MSG("StartNode INTERPRET");
	mProgramNode->Interpret();
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
void ProgramNode::Interpret()
{
	MSG("ProgramNode INTERPRET");
	mBlockNode->Interpret();
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
void BlockNode::Interpret()
{
	MSG("BlockNode INTERPRET");
	mStatementGroupNode->Interpret();
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
void StatementGroupNode::Interpret()
{
	MSG("StatementGroupNode INTERPRET");
	for(std::vector<StatementNode*>::iterator statement = mStatementNodes.begin(); statement != mStatementNodes.end(); statement++)
	{		
		(*statement)->Interpret();
	}
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
void DeclarationStatementNode::Interpret()
{
	MSG("DeclarationStatementNode INTERPRET");
	mIdentifierNode->DeclareVariable();
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
void AssignmentStatementNode::Interpret()
{	
	MSG("AssignmentStatementNode INTERPRET");
	int e = mExpressionNode->Evaluate();
	MSG(e);
	mIdentifierNode->SetValue(e);
	std::string y = mIdentifierNode->GetLabel();
	MSG(y);
	int x = mIdentifierNode->Evaluate();
	MSG(x);
};
/*
ExpressionNode::ExpressionNode()
{};
int ExpressionNode::sayhello()
{
	MSG("hello");
	return 0;
};
ExpressionNode::~ExpressionNode()
{ MSG("de-contruct ExpressionNode"); };
*/
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
void CoutStatementNode::Interpret()
{	
	MSG("CoutStatementNode INTERPRET");
	MSG((mExpressionNode));
	mExpressionNode->Evaluate();
	int e = mExpressionNode->Evaluate();
	MSG(e);
	
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
	MSG("IntegerNode EVALUATE");
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
	MSG("IdentifierNode EVALUATE");
	int x = mSymbolTable->GetValue(mLabel);
	return x;
};
std::string IdentifierNode::GetLabel()
{
	return mLabel;
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
	MSG("PlusNode EVALUATE");
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
	MSG("MinusNode EVALUATE");
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
	MSG("TimesNode EVALUATE");
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
	MSG("DivideNode EVALUATE");
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