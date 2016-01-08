#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/CardSet.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(CardSetTest)
	{
	public:

		TEST_METHOD(ShuffleTest)
		{
			BlueCard c0("BlueCard0", 1);
			BlueCard c1("BlueCard1", 2);
			BlueCard c2("BlueCard2", 3);
			BlueCard c3("BlueCard3", 4);
			BlueCard c4("BlueCard4", 5);
			BlueCard c5("BlueCard5", 6);
			BlueCard c6("BlueCard6", 7);
			BlueCard c7("BlueCard7", 8);
			CardSet set;
			set.push_back(&c0);
			set.push_back(&c1);
			set.push_back(&c2);
			set.push_back(&c3);
			set.push_back(&c4);
			set.push_back(&c5);
			set.push_back(&c6);
			set.push_back(&c7);
			set.shuffle();
			int value1 = 0;
			for (int i = 0; i < set.size(); i++){
				value1 += set.at(i)->getPoints() * i ;
			}

			BlueCard c00("BlueCard0", 1);
			BlueCard c10("BlueCard1", 2);
			BlueCard c20("BlueCard2", 3);
			BlueCard c30("BlueCard3", 4);
			BlueCard c40("BlueCard4", 5);
			BlueCard c50("BlueCard5", 6);
			BlueCard c60("BlueCard6", 7);
			BlueCard c70("BlueCard7", 8);
			CardSet set2;
			set2.push_back(&c00);
			set2.push_back(&c10);
			set2.push_back(&c20);
			set2.push_back(&c30);
			set2.push_back(&c40);
			set2.push_back(&c50);
			set2.push_back(&c60);
			set2.push_back(&c70);
			set2.shuffle();
			int value2 = 0;
			for (int i = 0; i < set2.size(); i++){
				value2 += set2.at(i)->getPoints() * i;
			}
			Assert::AreNotEqual(value1, value2);
		}
	};
}