#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/Marvel.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(MarvelDefaultTest)
	{
	public:
		
		TEST_METHOD(DefaultMarvelConstructor)
		{
			Marvel m(5);
			Assert::AreEqual(0, 0);
		}

	};
}