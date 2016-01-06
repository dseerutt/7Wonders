#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/BlueCard.cpp"
#include "../7Wonders/Card.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(0, 0);
			BlueCard c("ee", 5);
		}

	};
}