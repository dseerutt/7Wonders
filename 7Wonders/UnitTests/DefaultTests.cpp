#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(DefaultTests)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			// TODO: Ici, votre code de test
			Assert::AreEqual(0, 0);
			Assert::IsFalse(10 < 2);
			Assert::IsTrue(0 < 2);
			auto func = [this] { throw("Erreur"); };

			Assert::ExpectException<std::string>(func);
		}

	};
}