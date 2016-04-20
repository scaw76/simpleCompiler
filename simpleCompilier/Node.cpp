#include <iostream>
#include "Node.h"
#include "Debug.h"


// StartNode
StartNode::StartNode(ProgramNode * pn)
{
	mProgramNode = pn;
};
StartNode::~StartNode()
{
	//MSG("de-contruct StartNode");
	delete mProgramNode;
};
void StartNode::Interpret()
{
	//MSG("StartNode INTERPRET");
	mProgramNode->Interpret();
};
void StartNode::Code(InstructionsClass & machine)
{
	mProgramNode->Code(machine);
};

// Program Node
ProgramNode::ProgramNode(BlockNode * bn)
{
	mBlockNode = bn;
};
ProgramNode::~ProgramNode()
{
	//MSG("de-contruct ProgramNode");
	delete mBlockNode;
};
void ProgramNode::Interpret()
{
	//MSG("ProgramNode INTERPRET");
	mBlockNode->Interpret();
};
void ProgramNode::Code(InstructionsClass & machine)
{
	mBlockNode->Code(machine);
};

// Block Node
BlockNode::BlockNode(StatementGroupNode * sg)
	:StatementNode()
{
	mStatementGroupNode = sg;
};
BlockNode::~BlockNode()
{
	//MSG("de-contruct BlockNode");
	delete mStatementGroupNode;
};
void BlockNode::Interpret()
{
	//MSG("BlockNode INTERPRET");
	mStatementGroupNode->Interpret();
};
void BlockNode::Code(InstructionsClass & machine)
{
	mStatementGroupNode->Code(machine);
};

// Statement Group Node
StatementGroupNode::StatementGroupNode()
{};
StatementGroupNode::~StatementGroupNode()
{
	//MSG("de-contruct StatementGroupNode");
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
	//MSG("StatementGroupNode INTERPRET");
	for(std::vector<StatementNode*>::iterator statement = mStatementNodes.begin(); statement != mStatementNodes.end(); statement++)
	{		
		(*statement)->Interpret();
	}
};
void StatementGroupNode::Code(InstructionsClass & machine)
{
	for(std::vector<StatementNode*>::iterator statement = mStatementNodes.begin(); statement != mStatementNodes.end(); statement++)
	{		
		(*statement)->Code(machine);
	}
};

// Statement Node
StatementNode::StatementNode():Node(){};
StatementNode::~StatementNode()
{ 
	//MSG("de-contruct StatementNode"); 
};

// Declaration Statement Node
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode * id)
{
	mIdentifierNode = id;
};
DeclarationStatementNode::~DeclarationStatementNode()
{
	//MSG("de-contruct DeclarationStatementNode");
	delete mIdentifierNode;
};
void DeclarationStatementNode::Interpret()
{
	//MSG("DeclarationStatementNode INTERPRET");
	mIdentifierNode->DeclareVariable();
};
void DeclarationStatementNode::Code(InstructionsClass & machine)
{
	// declare variable
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
	//MSG("de-contruct AssignmentStatementNode");
	delete mIdentifierNode;
	delete mExpressionNode;
};
void AssignmentStatementNode::Interpret()
{	
	//MSG("AssignmentStatementNode INTERPRET");
	int e = mExpressionNode->Evaluate();
	//MSG(e);
	mIdentifierNode->SetValue(e);
	int x = mIdentifierNode->Evaluate();
	//MSG(x);
};
void AssignmentStatementNode::Code(InstructionsClass & machine)
{
	mExpressionNode->CodeEvaluate(machine);
	int index = mIdentifierNode->GetIndex();
	machine.PopAndStore(index);
	//mIdentifierNode->CodeEvaluate(machine);
};

// Expression Node
ExpressionNode::ExpressionNode()
{};
ExpressionNode::~ExpressionNode()
{};

// Cout Statement Node
CoutStatementNode::CoutStatementNode(ExpressionNode * en)
	:StatementNode()
{
	mExpressionNode = en;
};
CoutStatementNode::~CoutStatementNode()
{
	//MSG("de-contruct CoutStatementNode");
	delete mExpressionNode;
};
void CoutStatementNode::Interpret()
{	
	//MSG("CoutStatementNode INTERPRET");
	int e = mExpressionNode->Evaluate();
	MSG(e);	
};
void CoutStatementNode::Code(InstructionsClass & machine)
{
	mExpressionNode->CodeEvaluate(machine);
	machine.PopAndWrite();
};

// If Statement Node
IfStatementNode::IfStatementNode(ExpressionNode * en,  StatementGroupNode *sg)
	:StatementNode()
{
	mExpressionNode = en;
	mStatementGroupNode = sg;
};
IfStatementNode::~IfStatementNode()
{
	//MSG("de-contruct IfStatementNode");
	delete mExpressionNode;
	delete mStatementGroupNode;
};
void IfStatementNode::Interpret()
{	
	//MSG("IfStatementNode INTERPRET");
	//MSG("Here " <<mExpressionNode->Evaluate() );
	if(mExpressionNode->Evaluate())
		mStatementGroupNode->Interpret();
};
/**** NEED TO FIGURE OUT **********************************/
void IfStatementNode::Code(InstructionsClass & machine)
{
	//if
	mExpressionNode->CodeEvaluate(machine);
	//then
	mStatementGroupNode->Code(machine);
};

// While Statement Node
WhileStatementNode::WhileStatementNode(ExpressionNode * en, StatementGroupNode *sg)
	:StatementNode()
{
	mExpressionNode = en;
	mStatementGroupNode = sg;
};
WhileStatementNode::~WhileStatementNode()
{
	//MSG("de-contruct WhileStatementNode");
	delete mExpressionNode;
	delete mStatementGroupNode;
};
void WhileStatementNode::Interpret()
{	
	//MSG("WhileStatementNode INTERPRET");
	while(mExpressionNode->Evaluate())
	{
		mStatementGroupNode->Interpret();
		mExpressionNode->Evaluate();
	}		
};
void WhileStatementNode::Code(InstructionsClass & machine)
{
	//WHILE
	mExpressionNode->CodeEvaluate(machine);
	// THEN
	mStatementGroupNode->Code(machine);
	mExpressionNode->CodeEvaluate(machine);

};

// Repeat Statement Node
RepeatStatementNode::RepeatStatementNode(ExpressionNode * en, StatementGroupNode *sg)
	:StatementNode()
{
	mExpressionNode = en;
	mStatementGroupNode = sg;
};
RepeatStatementNode::~RepeatStatementNode()
{
	//MSG("de-contruct WhileStatementNode");
	delete mExpressionNode;
	delete mStatementGroupNode;
};
void RepeatStatementNode::Interpret()
{	
	int i = mExpressionNode->Evaluate();
	for(int x=0;x<i;x++)
	{
		mStatementGroupNode->Interpret();
	}		
};
void RepeatStatementNode::Code(InstructionsClass & machine)
{	
	mExpressionNode->CodeEvaluate(machine);
	// execute that many times
		mStatementGroupNode->Code(machine);
};

// Integer Node
IntegerNode::IntegerNode(int i)
	:ExpressionNode()
{
	mInteger = i;
};
IntegerNode::~IntegerNode()
{ 
	//MSG("de-contruct IntegerNode"); 
};
int IntegerNode::Evaluate()
{
	//MSG("IntegerNode EVALUATE");
	return mInteger;
};
void IntegerNode::CodeEvaluate(InstructionsClass &machine)
{
	MSG("push value: "<<mInteger);
	machine.PushValue(mInteger);
};

// Identifier Node
IdentifierNode::IdentifierNode(std::string label, SymbolTableClass * st)
{
	mLabel = label;
	mSymbolTable = st;
};
IdentifierNode::~IdentifierNode()
{
	//MSG("de-contruct IdentifierNode");
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
	//MSG("IdentifierNode EVALUATE");
	int x = mSymbolTable->GetValue(mLabel);
	//MSG(x);
	return x;
};
void IdentifierNode::CodeEvaluate(InstructionsClass &machine)
{
	machine.PushVariable(GetIndex());
	MSG("push variable index: "<< GetIndex());
};
std::string IdentifierNode::GetLabel()
{
	return mLabel;
};

// Binary Operator Node
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * lhs, ExpressionNode * rhs)
	:ExpressionNode()
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
	//MSG(left <<" + " <<right);
	return left + right;
};
void PlusNode::CodeEvaluate(InstructionsClass &machine)
{	
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	MSG("pop pop add push: ");
	machine.PopPopAddPush();
	
};

// Minus Node
MinusNode::MinusNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int MinusNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left<< " - " <<right);
	return left - right;
};
void MinusNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopSubPush();
};

// Times Node
TimesNode::TimesNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int TimesNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" * " <<right);
	return left * right;
};
void TimesNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopMulPush();
};
// Divide Node
DivideNode::DivideNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int DivideNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" / " <<right);
	return left/right;
	
};
void DivideNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopDivPush();
};

// Less Node
LessNode::LessNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int LessNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" < " <<right);
	return left < right;
};
void LessNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopLessPush();
};

// Less Equal Node
LessEqualNode::LessEqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int LessEqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" <= " <<right);
	return left <= right;
};
void LessEqualNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopLessEqualPush();
};

// Greater Node
GreaterNode::GreaterNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int GreaterNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" > " <<right);
	return left > right;
};
void GreaterNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopGreaterPush();
};

// Greater Equal Node
GreaterEqualNode::GreaterEqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int GreaterEqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left<< " >= "<< right);
	return left >= right;
};
void GreaterEqualNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopGreaterEqualPush();
};
// Equal Node
EqualNode::EqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int EqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" == "<< right);
	return left == right;
};
void EqualNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopEqualPush();
};
// Not Equal Node
NotEqualNode::NotEqualNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int NotEqualNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" != "<< right);
	return left != right;
};
void NotEqualNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopNotEqualPush();
};

 // And Node
AndNode::AndNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int AndNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" && "<< right);
	return (left && right);
};
void AndNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopAndPush();
};

 // Or Node
OrNode::OrNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs,rhs)
{};
 int OrNode::Evaluate()
{
	int left = this->mLeft->Evaluate();
	int right = this->mRight->Evaluate();
	//MSG(left <<" || "<< right);
	return (left || right);
};
void OrNode::CodeEvaluate(InstructionsClass &machine)
{
	mLeft->CodeEvaluate(machine);
	mRight->CodeEvaluate(machine);
	machine.PopPopOrPush();
};