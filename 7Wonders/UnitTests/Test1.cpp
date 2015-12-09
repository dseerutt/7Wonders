#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\7Wonders\BlueCard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTests
{
	TEST_CLASS(ColorCards)
	{
	public:

		TEST_METHOD(BlueCard2)
		{
			BlueCard bluecard("rr", 5);
			//Assert::AreEqual(5, b.m_points);

			// TODO: Ici, votre code de test
			Assert::AreEqual(0, 0);
			Assert::IsFalse(10 < 2);
			Assert::IsTrue(0 < 2);
		}

	};
}