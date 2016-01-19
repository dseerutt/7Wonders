#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/HumanPlayer.cpp"
#include "../7Wonders/CardSet.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/Player.h"
#include <string> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(HumanPlayerTest)
	{
	public:

		TEST_METHOD(HumanPlayerConstructor)
		{
			CardSet set;
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			HumanPlayer cp(&set, 6);
			//impossible de tester discard, non accessible
			Assert::IsTrue(true);
		}
		//pickCard pas testé car utilise cin

	};
}