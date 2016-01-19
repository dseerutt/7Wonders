#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/ComputerPlayer.cpp"
#include "../7Wonders/CardSet.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/Player.cpp"
#include <string> 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(ComputerPlayerTest)
	{
	public:
		
		TEST_METHOD(ComputerPlayerConstructor)
		{
			CardSet set;
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set,6);
			//impossible de tester discard, non accessible
			Assert::IsTrue(true);
		}

		TEST_METHOD(PickCardTestComputer)
		{
			CardSet set;
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set, 6);


			CardSet hand;
			BlueCard card0("carte bleue0", 1, "-");
			BlueCard card1("carte bleue1", 2, "-");
			BlueCard card2("carte bleue2", 3, "-");
			BlueCard card3("carte bleue3", 4, "-");
			BlueCard card4("carte bleue4", 5, "-");
			BlueCard card5("carte bleue5", 6, "-");
			BlueCard card6("carte bleue6", 7, "-");
			BlueCard card7("carte bleue7", 8, "-");
			hand.push_back(&card0);
			hand.push_back(&card1);
			hand.push_back(&card2);
			hand.push_back(&card3);
			hand.push_back(&card4);
			hand.push_back(&card5);
			hand.push_back(&card6);
			hand.push_back(&card7);
			cp.setHand(hand);
			
			cp.prepareTurn(); //Appel de pickCard, champ protected
			//PickACard n'élimine pas la carte choisie
			Assert::AreEqual(8, (int)cp.getHand().size());
			cp.playTurn();
			//playTurn élimine la carte choisie
			Assert::AreEqual(7, (int) cp.getHand().size());
		}

		TEST_METHOD(pickCardSameCardTest)
		{
			//Une seule sélection doit donner la même carte
			CardSet set;
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set, 6);


			CardSet hand;
			BlueCard card0("carte bleue0", 1, "-");
			BlueCard card1("carte bleue1", 2, "-");
			BlueCard card2("carte bleue2", 3, "-");
			BlueCard card3("carte bleue3", 4, "-");
			BlueCard card4("carte bleue4", 5, "-");
			BlueCard card5("carte bleue5", 6, "-");
			BlueCard card6("carte bleue6", 7, "-");
			BlueCard card7("carte bleue7", 8, "-");
			hand.push_back(&card0);
			hand.push_back(&card1);
			hand.push_back(&card2);
			hand.push_back(&card3);
			hand.push_back(&card4);
			hand.push_back(&card5);
			hand.push_back(&card6);
			hand.push_back(&card7);
			cp.setHand(hand);

			cp.prepareTurn(); //Appel de pickCard, champ protected
			cp.playTurn();
			string t = to_string((int)cp.getBoard().size());
			int value = cp.getBoard().at(0)->getPoints();


			CardSet set2;
			BlueCard card222("carte bleue", 5, "-");
			set2.push_back(&card222);
			ComputerPlayer cp2(&set, 6);


			CardSet hand2;
			BlueCard card02("carte bleue0", 1, "-");
			BlueCard card12("carte bleue1", 2, "-");
			BlueCard card22("carte bleue2", 3, "-");
			BlueCard card32("carte bleue3", 4, "-");
			BlueCard card42("carte bleue4", 5, "-");
			BlueCard card52("carte bleue5", 6, "-");
			BlueCard card62("carte bleue6", 7, "-");
			BlueCard card72("carte bleue7", 8, "-");
			hand2.push_back(&card02);
			hand2.push_back(&card12);
			hand2.push_back(&card22);
			hand2.push_back(&card32);
			hand2.push_back(&card42);
			hand2.push_back(&card52);
			hand2.push_back(&card62);
			hand2.push_back(&card72);
			cp2.setHand(hand2);

			cp2.prepareTurn(); //Appel de pickCard, champs protected
			cp2.playTurn();
			int value1 = cp2.getBoard().at(0)->getPoints();
			Assert::AreEqual(value, value1);
		}

	};
}