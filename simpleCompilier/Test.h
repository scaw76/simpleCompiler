#pragma once
#ifndef _TEST_
#define _TEST_


#include <vector>


class Test{
public:
	Test(std::string name, bool condition);
	std::string mName;
	bool mPassed;
};
class UnitTest{
public:
	UnitTest(std::string name);
	void AddTest(Test t);
	bool Evaluate();
	std::vector<Test> mTests;
	std::string mName;
};
#endif //_TEST_