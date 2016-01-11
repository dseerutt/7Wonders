#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/HumanPlayer.h"
#include "../7Wonders/ComputerPlayer.h"
#include "../7Wonders/World.cpp"
#include "../7Wonders/Player.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(HumanPlayerTest)
	{
	public:

		TEST_METHOD(NumberOfAges)
		{
			Assert::AreEqual(3, NUMBER_OF_AGES);
		}

		TEST_METHOD(WorldConstructor)
		{
			World w(3, 2);
			Assert::IsFalse(w.m_gameOver);
			Assert::AreEqual((unsigned)0, w.m_age);
			Assert::AreEqual(5, (int)w.m_players.size());
			//2 tests suivants utiles ?
			//Assert::AreEqual(3, (int)w.m_humanPlayers.size());
			//Assert::AreEqual(2, (int)w.m_computerPlayers.size());

			Assert::AreEqual(0, (int)w.m_deck.size());
			Assert::AreEqual(0, (int)w.m_discard.size());
			Assert::AreEqual(false, w.m_draw);
			for (int i = 0; i < w.m_scores.size(); i++)
			{
				for (int j = 0; j < 8; j++)
				{
					Assert::AreEqual(0, (int)w.m_scores.at(i).at(j));
				}
			}
		}

		TEST_METHOD(WorldDestructor)
		{
			World w(3, 2);
			Assert::AreEqual(5, (int)w.m_players.size());
			w.~World();
			Assert::AreEqual(0, (int)w.m_players.size());
		}

		TEST_METHOD(PlayTest)
		{
			World w(3, 2);
			ComputerPlayer* p = (ComputerPlayer*) w.m_players[3];
			w.startAge();
			Assert::AreEqual(7, (int)p->getHand().size());
			w.play(*p);
			Assert::AreEqual(7, (int) p->getHand().size());
			p->playTurn();
			Assert::AreEqual(6, (int)p->getHand().size());
		}

		TEST_METHOD(StartAgeTest)
		{
			World w(3, 2);
			ComputerPlayer* p = (ComputerPlayer*)w.m_players[3];
			w.startAge();
			Assert::AreEqual(1, (int) w.m_age);
			Assert::AreEqual(7, (int) p->getHand().size());
//			p->getHand().clear();

			w.startAge();
			Assert::AreEqual(2, (int)w.m_age);
			Assert::AreNotEqual(0, (int)p->getHand().size());
		}

		TEST_METHOD(PlayOtherTest)
		{
			//test seulement des computer players
			World w(0, 3);
			ComputerPlayer* p0 = (ComputerPlayer*)w.m_players[0];
			ComputerPlayer* p1 = (ComputerPlayer*)w.m_players[1];
			ComputerPlayer* p = (ComputerPlayer*)w.m_players[2];
			w.startAge();
			Assert::AreEqual(7, (int)p->getHand().size());
			Assert::AreEqual(7, (int)p0->getHand().size());
			Assert::AreEqual(7, (int)p1->getHand().size());
			w.playOthers(*p);
			Assert::AreEqual(7, (int)p0->getHand().size());
			Assert::AreEqual(7, (int)p1->getHand().size());
			Assert::AreEqual(7, (int)p->getHand().size());
			try{
				p0->playTurn();
				p1->playTurn();
				p->playTurn();
			}
			catch (std::exception e){
			}
			Assert::AreEqual(6, (int)p->getHand().size());
			Assert::AreEqual(6, (int)p0->getHand().size());
			Assert::AreEqual(6, (int)p1->getHand().size());
		}

		TEST_METHOD(PlayTurnTest)
		{
			World w(0, 5);
			ComputerPlayer* p = (ComputerPlayer*)w.m_players[3];
			w.startAge();
			w.play(*p);
			w.playOthers(*p);
			w.playTurn();
			for (int i = 0; i < w.m_players.size(); i++)
			{
				Assert::AreEqual(6, (int) w.m_players.at(i)->getHand().size());
			}
			
		}

		/*bool m_gameOver;
	unsigned int m_age;
	std::vector<HumanPlayer> m_humanPlayers;
	std::vector<ComputerPlayer> m_computerPlayers;
	CardSet m_deck;
	CardSet m_discard;
	std::vector<Player*> m_players;
	std::vector<std::vector<unsigned int> > m_scores;
	const Player* m_winner;
	bool m_draw;

	void run();
	void endTurn();
	void startAge();
	bool betweenTurns() const;
	bool gameOver() const;
	void processTurn();
	CardSet generateDeck(int age);
	void distributeCards();
	void draft(unsigned int age);
	void prepareTurn();
	void playTurn();
	void computeScores();
	void displayScores() const;
	unsigned int computeScienceScore(const CardSet& board) const;
	bool hasWon(const Player& player) const;
	bool draw() const;
	unsigned int getPlayerId(const Player& player) const;*/

	};
}