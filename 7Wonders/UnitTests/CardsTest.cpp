#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/Card.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(CardsTest)
	{
	public:
		//impossible de tester la classe Card.cpp directement car c'est une classe virtuelle pure
		//elle contient un élément de type virtuel dans le header
		
		TEST_METHOD(BlueCardConstructor)
		{
			BlueCard c("nomCarte", 5);
			Assert::AreEqual((unsigned)5, c.getPoints());
			;
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			//Assert::AreEqual(BLUE, c.m_color);

		}

		TEST_METHOD(BlueGetPoints)
		{
			BlueCard c("ee", 5);
			Assert::AreEqual((unsigned)5, c.getPoints());
		}

	};
}