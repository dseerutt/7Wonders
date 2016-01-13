#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/Player.h"
#include "../7Wonders/ComputerPlayer.h"
#include "../7Wonders/CardSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PlayerTest)
	{
	public:
		
		TEST_METHOD(PlayerConstructor)
		{
			CardSet set;
			BlueCard card("carte bleue", 5);
			set.push_back(&card);
			ComputerPlayer cp(&set);
			Assert::IsTrue(cp.getBoard().empty());
			Assert::AreEqual((unsigned) 0, cp.getScore());
			Assert::AreEqual((unsigned) 0, cp.getMoney());
			Assert::IsTrue(cp.getBoard().empty());
			Assert::IsTrue(cp.getHand().empty());
			//pas de test de m_discard, m_cardToPlay car protected
		}

		TEST_METHOD(GetMoneyTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::AreEqual((unsigned)0, cp.getMoney());
		}

		TEST_METHOD(CanBuyTest)
		{
			//TODO
			Assert::AreEqual(0, 1);
		}

		TEST_METHOD(GetScoreTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::AreEqual((unsigned)0, cp.getScore());
		}

		TEST_METHOD(GetMilitaryTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::AreEqual((unsigned)0, cp.getMilitary());
		}

		TEST_METHOD(GetBoardTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::IsTrue(cp.getBoard().empty());
		}

		TEST_METHOD(SetHandTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::IsTrue(cp.getHand().empty());

			CardSet set2;
			BlueCard card("carte bleue", 5);
			set2.push_back(&card);
			cp.setHand(set2);
			Assert::IsTrue(!cp.getHand().empty());
			Assert::AreEqual(set2.at(0)->m_name, cp.getHand().at(0)->m_name);
		}

		TEST_METHOD(GetHandTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::IsTrue(cp.getHand().empty());
			CardSet set2;
			BlueCard card("carte bleue", 5);
			set2.push_back(&card);
			cp.setHand(set2);
			Assert::AreEqual(set2.at(0)->m_name, cp.getHand().at(0)->m_name);
		}

		TEST_METHOD(PrepareTurnETPlayTurnTest)
		{
			CardSet set;
			BlueCard card("carte bleue", 5);
			set.push_back(&card);
			ComputerPlayer cp(&set);

			CardSet hand;
			BlueCard card0("carte bleue0", 1);
			BlueCard card1("carte bleue1", 2);
			BlueCard card2("carte bleue2", 3);
			BlueCard card3("carte bleue3", 4);
			BlueCard card4("carte bleue4", 5);
			BlueCard card5("carte bleue5", 6);
			BlueCard card6("carte bleue6", 7);
			BlueCard card7("carte bleue7", 8);
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
			Assert::AreEqual(7, (int)cp.getHand().size());
		}

		TEST_METHOD(playTurnTestBadCases1)
		{
			CardSet set;
			BlueCard card("carte bleue", 5);
			set.push_back(&card);
			ComputerPlayer cp(&set);
			CardSet hand;
			BlueCard card0("carte bleue0", 1);
			BlueCard card1("carte bleue1", 2);
			BlueCard card7("carte bleue7", 8);
			hand.push_back(&card0);
			hand.push_back(&card1);
			hand.push_back(&card7);
			cp.setHand(hand);

			try {
				cp.playTurn();
			}
			catch (const char* & ex){
				Assert::AreEqual("Pas de carte à jouer sélectionnée", ex);
			}
		}

		TEST_METHOD(playTurnTestBadCases2)
		{
			CardSet set;
			BlueCard card("carte bleue", 5);
			set.push_back(&card);
			ComputerPlayer cp(&set);
			CardSet hand;
			BlueCard card0("carte bleue0", 1);
			BlueCard card1("carte bleue1", 2);
			BlueCard card7("carte bleue7", 8);
			hand.push_back(&card0);
			hand.push_back(&card1);
			hand.push_back(&card7);
			cp.setHand(hand);

			cp.prepareTurn();
			hand.clear();
			hand.push_back(&card0);
			cp.setHand(hand);

			try {
				cp.playTurn();
			}
			catch (const char* & ex){
				Assert::AreEqual("Taille de la main non conforme", ex);
			}
		}

		TEST_METHOD(PrepareTurnTestBadCases1)
		{
			CardSet set;
			BlueCard card("carte bleue", 5);
			set.push_back(&card);
			ComputerPlayer cp(&set);
			CardSet hand;
			cp.setHand(hand);
			try {
				cp.prepareTurn();
			}
			catch (const char* & ex){
				Assert::AreEqual("Un joueur ne possède aucune carte en main", ex);
			}
		}
	};
}