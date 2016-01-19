#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/BrownCard.cpp"
#include "../7Wonders/GrayCard.cpp"
#include "../7Wonders/GreenCard.cpp"
#include "../7Wonders/RedCard.cpp"
#include "../7Wonders/YellowCard.cpp"
#include "../7Wonders/VioletCard.h"
#include "../7Wonders/Card.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(CardColorTest)
	{
	public:
		//impossible de tester la classe Card.cpp directement car c'est une classe virtuelle pure
		//elle contient un élément de type virtuel dans le header
		
		TEST_METHOD(BlueCardConstructor)
		{
			BlueCard c("nomCarte", 5, "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)BLUE, (int)c.m_color);
			Assert::AreEqual((unsigned)5, c.getPoints());
		}

		TEST_METHOD(BlueGetPoints)
		{
			BlueCard c("ee", 5, "-");
			Assert::AreEqual((unsigned)5, c.getPoints());
		}

		TEST_METHOD(BrownCardConstructor)
		{
			BrownCard c("nomCarte", "prod", "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)BROWN, (int)c.m_color);
			Assert::AreEqual((unsigned)0, c.getPoints());
			Assert::AreEqual("prod", c.getProduction().c_str());
		}

		TEST_METHOD(BrownGetPoints)
		{
			BrownCard c("ee", "prod", "-");
			Assert::AreEqual((unsigned)0, c.getPoints());
		}

		TEST_METHOD(BrownGetProduction)
		{
			BrownCard c("ee", "prod", "-");
			Assert::AreEqual("prod", c.getProduction().c_str());
		}

		TEST_METHOD(GrayCardConstructor)
		{
			GrayCard c("nomCarte", "prod", "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)GRAY, (int)c.m_color);
			Assert::AreEqual((unsigned)0, c.getPoints());
			Assert::AreEqual("prod", c.getProduction().c_str());
		}

		TEST_METHOD(GrayGetPoints)
		{
			GrayCard c("ee", "prod", "-");
			Assert::AreEqual((unsigned)0, c.getPoints());
		}

		TEST_METHOD(GrayGetProduction)
		{
			GrayCard c("ee", "prod", "-");
			Assert::AreEqual("prod", c.getProduction().c_str());
		}

		TEST_METHOD(GreenCardConstructor)
		{
			GreenCard c("nomCarte", 't', "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)GREEN, (int)c.m_color);
			Assert::AreEqual((unsigned)0, c.getPoints());
			Assert::AreEqual('t', c.getType());
		}

		TEST_METHOD(GreenGetPoints)
		{
			GreenCard c("ee", 't', "-");
			Assert::AreEqual((unsigned)0, c.getPoints());
		}

		TEST_METHOD(GreenGetType)
		{
			GreenCard c("ee", 't', "-");
			Assert::IsTrue('t' == c.getType());
		}


		TEST_METHOD(RedCardConstructor)
		{
			RedCard c("nomCarte", 2, "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)RED, (int)c.m_color);
			Assert::AreEqual((unsigned)0, c.getPoints());
			Assert::AreEqual((unsigned)2, c.getPower());
		}

		TEST_METHOD(RedGetPoints)
		{
			RedCard c("ee", 2, "-");
			Assert::AreEqual((unsigned)0, c.getPoints());
		}



		TEST_METHOD(RedGetPower)
		{
			RedCard c("ee", 2, "-");
			Assert::AreEqual((unsigned)2, c.getPower());
		}

		TEST_METHOD(YellowCardConstructor)
		{
			YellowCard c("nomCarte", "", "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)YELLOW, (int)c.m_color);
			Assert::AreEqual((unsigned)0, c.getPoints());
		}

		TEST_METHOD(YellowGetPoints)
		{
			YellowCard c("ee", "", "-");
			Assert::AreEqual((unsigned)0, c.getPoints());
		}
		
		TEST_METHOD(VioletCardConstructor)
		{
			VioletCard c("nomCarte", "", "-");
			Assert::AreEqual("nomCarte", c.m_name.c_str());
			Assert::AreEqual((int)VIOLET, (int)c.m_color);
			Assert::AreEqual((unsigned)0, c.getPoints());
		}

		TEST_METHOD(VioletGetPoints)
		{
			VioletCard c("ee", "", "-");
			Assert::AreEqual((unsigned)0, c.getPoints());
		}
	};
}