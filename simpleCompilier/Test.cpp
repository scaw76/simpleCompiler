#include "Test.h"
#include "Debug.h"
#include <string>
#include <iostream>
Test::Test(std::string name, bool condition)
{
	mName =name;
	mPassed = condition;
};
	
UnitTest::UnitTest(std::string name)
	:mName(name)
{};

void UnitTest::AddTest(Test t)
{
	mTests.push_back(t);
};
bool UnitTest::Evaluate()
{
	for(std::vector<Test>::iterator it = mTests.begin(); it != mTests.end(); it++)
	{
		if(!(it->mPassed))
		{
			FAILED(mName);
			FAILED(it->mName);
			system("pause");
			exit(0);
			return false;
		}
	}
	PASSED(mName);
	return true;
};
	