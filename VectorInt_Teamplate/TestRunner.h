#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <sstream>

class TestRunner
{
private:
	struct TestResponse
	{
		bool mIsOk = true;
		std::string mMessage;
	};

	std::vector<TestResponse> mResponses;

	TestRunner() {}	
public:
	TestRunner(const TestRunner&) = delete;
	~TestRunner() = default;

	void TestFailed(const char* fileName, int lineNo);

	void RunTest(std::function<bool()> func, const char* funcName);
	void ShowAndClear(std::ostream& out = std::cout);	

	static TestRunner& GetTestRunner();
};

TestRunner& TestRunner::GetTestRunner()
{
	static TestRunner runner;
	return runner;
}

inline
void TestRunner::RunTest(std::function<bool()> func, const char* funcName)
{
	bool ans = func();
	std::stringstream stream;
	stream << "Test " << funcName << ": ";
	if (ans)
		stream << " Passed";
	else
		stream << " Failed";
	mResponses.push_back({ ans, stream.str() });
}

inline
void TestRunner::ShowAndClear(std::ostream& out)
{
	for (auto& resp : mResponses)
		out << resp.mMessage << std::endl;
	mResponses.clear();
}

inline
void TestRunner::TestFailed(const char* fileName,int lineNo)
{
	std::stringstream stream;
	stream << "Test failed in file: " << fileName;
	stream << "; on line: " << lineNo;
	mResponses.push_back({ false, stream.str() });
}

#define RUN_TEST(func) TestRunner::GetTestRunner().RunTest(func, #func);

#define SHOW_RESULTS() TestRunner::GetTestRunner().ShowAndClear();

#define TRUE_REQUIRE(ans) \
	if(!(ans)) {	\
		TestRunner::GetTestRunner().TestFailed(__FILE__, __LINE__);	\
		return false; }

#define EQUAL_REQUIRE(a, b) \
	if(!(a == b)) {	\
		TestRunner::GetTestRunner().TestFailed(__FILE__, __LINE__);	\
		return false; }