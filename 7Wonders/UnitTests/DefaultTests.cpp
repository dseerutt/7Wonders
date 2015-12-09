#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(DefaultTests)
	{
	public:

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