#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/HumanPlayer.h"
#include "../7Wonders/ComputerPlayer.h"
#include "../7Wonders/World.cpp"
#include "../7Wonders/Player.h"
#include <string>
#include <regex>
#include <stdio.h>
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

		TEST_METHOD(GameOverTest)
		{
			World w(3, 2);
			Assert::IsFalse(w.gameOver());
			w.m_gameOver = true;
			Assert::IsTrue(w.gameOver());
		}

		TEST_METHOD(DrawTest)
		{
			World w(3, 2);
			Assert::IsFalse(w.draw());
			w.m_draw = true;
			Assert::IsTrue(w.draw());
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
			CardSet set;
			p->setHand(set);

			Assert::AreEqual(0, (int)p->getHand().size());
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

		TEST_METHOD(GenerateDeck3PlayersTest)
		{
			//3 joueurs
			CardDatabaseParser parser(3);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)21, set.size());
			set = parser.generateDeck(1);
			Assert::AreEqual((size_t)21, set.size());
			set = parser.generateDeck(2);
			Assert::AreEqual((size_t)21, set.size());
		}

		TEST_METHOD(GetPlayerIdTest)
		{
			World w(2, 5);
			for (int i = 0; i < w.m_players.size(); i++)
			{
				Assert::AreEqual((unsigned) i, w.getPlayerId(*(w.m_players[i])));
			}
		}

		TEST_METHOD(HasWonTest)
		{
			World w(2, 5);
			for (int i = 0; i < w.m_players.size(); i++)
			{
				Assert::IsFalse(w.hasWon(*(w.m_players[i])));
			}
			w.m_winner = w.m_players[3];
			Assert::IsTrue(w.hasWon(*(w.m_players[3])));
		}

		TEST_METHOD(TestingScore)
		{
			Assert::AreEqual(1, 0);
			//Need to check the score
		}

		TEST_METHOD(ComputeScienceScoreTest)
		{
			Assert::AreEqual(1, 0);
			//Need to check the score
		}

		TEST_METHOD(ComputeScoreTest)
		{
			Assert::AreEqual(1, 0);
			//Need to check the score
		}

		TEST_METHOD(EndTurntest)
		{
			Assert::AreEqual(1, 0);
			//TODO
		}

		TEST_METHOD(RunTest)
		{
			Assert::AreEqual(1, 0);
			//TODO
		}

		TEST_METHOD(BetweenTurntest)
		{
			//ToCheck
			World w(0, 3);
			CardSet set;
			Assert::IsTrue(w.betweenTurns());
			w.generateDeck(0);
			w.distributeCards();
			Assert::IsFalse(w.betweenTurns());
			/*
			m_players[0].s
			m_players[0]->getHand().size() <= 1;*/
		}

		TEST_METHOD(ProcessTurntest)
		{
			//TODO
			Assert::IsTrue(false);
		}

		TEST_METHOD(DraftTest)
		{
			//TODO
			Assert::IsTrue(false);
		}

		TEST_METHOD(DistributeCardtest)
		{
			//TODO
			World w(1, 2);
			w.generateDeck(0);
			w.distributeCards();
			Assert::AreEqual(0,(int) w.m_players[0]->getHand().size());
		}

	};
}