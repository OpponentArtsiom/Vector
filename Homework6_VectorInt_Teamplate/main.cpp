#include <iostream>
#include <vector>
#include <memory>

#include "Vector.h"
#include "TestRunner.h"

using namespace std;

struct TestStruct
{
	static int copyCounter;
	static int createCounter;
	static int moveCounter;
	static void SkipCounters()
	{
		copyCounter = 0;
		createCounter = 0;
		moveCounter = 0;
	}

	TestStruct() { ++createCounter; }
	TestStruct(const TestStruct&) { ++copyCounter; }
	TestStruct(TestStruct&&) { ++moveCounter; }

	const TestStruct& operator = (const TestStruct&) { ++copyCounter; return *this; }
	const TestStruct& operator = (TestStruct&&) { ++moveCounter; return *this; }
};

int TestStruct::copyCounter = 0;
int TestStruct::createCounter = 0;
int TestStruct::moveCounter = 0;
//==============================================
bool Vector_Test1()
{
	TRUE_REQUIRE(is_move_constructible<Vector<int>>::value);
	TRUE_REQUIRE(is_move_assignable<Vector<int>>::value);
	
	Vector<TestStruct> v1(5, TestStruct());
	TestStruct::SkipCounters();
	Vector<TestStruct> v2 = std::move(v1);
	TRUE_REQUIRE(v1.Empty());
	EQUAL_REQUIRE(v2.Size(), 5);
	EQUAL_REQUIRE(TestStruct::createCounter, 0);
	EQUAL_REQUIRE(TestStruct::copyCounter, 0);
	EQUAL_REQUIRE(TestStruct::moveCounter, 0);

	
	v1 = std::move(v2);
	TRUE_REQUIRE(v2.Empty());
	
	EQUAL_REQUIRE(v1.Size(), 5);
	EQUAL_REQUIRE(TestStruct::createCounter, 0);
	EQUAL_REQUIRE(TestStruct::copyCounter, 0);
	EQUAL_REQUIRE(TestStruct::moveCounter, 0);
	
	return true;
}

int main()
{
	RUN_TEST(Vector_Test1);

	SHOW_RESULTS();
}