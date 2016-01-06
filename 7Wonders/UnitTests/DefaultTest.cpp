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

		TEST_METHOD(DefaultTestsMethod)
		{
			// TODO: Ici, votre code de test
			Assert::AreEqual(0, 0);
			Assert::IsFalse(10 < 2);
			Assert::IsTrue(0 < 2);
			auto func = [this] { throw(1); };

			Assert::ExpectException<int>(func);


			auto func2 = [this] { throw("rr"); };

			Assert::ExpectException<char*>(func2); //Pas string
		}
	};
}