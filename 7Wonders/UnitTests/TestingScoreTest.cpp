#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/HumanPlayer.h"
#include "../7Wonders/ComputerPlayer.h"
#include "../7Wonders/World.h"
#include "../7Wonders/Player.h"
#include <string>
#include <regex>
#include <stdio.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(TestingScoreTest)
	{
	public:
		
		TEST_METHOD(TestingWar)
		{
			World w(0, 3);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					int v0 = w.m_scores.at(0).at(WAR);
					int v1 = w.m_scores.at(1).at(WAR);
					int v2 = w.m_scores.at(2).at(WAR);
					w.updateMilitary();
					int factor = 0;
					if (w.m_age == 1)
					{
						factor = 1;
					}
					if (w.m_age == 2)
					{
						factor = 3;
					}
					if (w.m_age == 3)
					{
						factor = 5;
					}
					int newValue;
					//J 1
					newValue = 0;
					if (w.m_players.at(0)->getMilitary() > w.m_players.at(0)->leftNeighbor->getMilitary())
					{
						newValue += factor;
					}
					if (w.m_players.at(0)->getMilitary() < w.m_players.at(0)->leftNeighbor->getMilitary())
					{
						newValue += -1;
					}
					if (w.m_players.at(0)->getMilitary() > w.m_players.at(0)->rightNeighbor->getMilitary())
					{
						newValue += factor;
					}
					if (w.m_players.at(0)->getMilitary() < w.m_players.at(0)->rightNeighbor->getMilitary())
					{
						newValue += -1;
					}
					Assert::AreEqual(newValue + v0, w.m_scores.at(0).at(WAR));

					//J2
					newValue = 0;
					if (w.m_players.at(1)->getMilitary() > w.m_players.at(1)->leftNeighbor->getMilitary())
					{
						newValue += factor;
					}
					if (w.m_players.at(1)->getMilitary() < w.m_players.at(1)->leftNeighbor->getMilitary())
					{
						newValue += -1;
					}
					if (w.m_players.at(1)->getMilitary() > w.m_players.at(1)->rightNeighbor->getMilitary())
					{
						newValue += factor;
					}
					if (w.m_players.at(1)->getMilitary() < w.m_players.at(1)->rightNeighbor->getMilitary())
					{
						newValue += -1;
					}
					Assert::AreEqual(newValue + v1, w.m_scores.at(1).at(WAR));

					//J3
					 newValue = 0;
					if (w.m_players.at(2)->getMilitary() > w.m_players.at(2)->leftNeighbor->getMilitary())
					{
						newValue += factor;
					}
					if (w.m_players.at(2)->getMilitary() < w.m_players.at(2)->leftNeighbor->getMilitary())
					{
						newValue += -1;
					}
					if (w.m_players.at(2)->getMilitary() > w.m_players.at(2)->rightNeighbor->getMilitary())
					{
						newValue += factor;
					}
					if (w.m_players.at(2)->getMilitary() < w.m_players.at(2)->rightNeighbor->getMilitary())
					{
						newValue += -1;
					}
					Assert::AreEqual(newValue + v2, w.m_scores.at(2).at(WAR));

					w.startAge();
				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			Assert::IsTrue(w.m_gameOver);
		}

		TEST_METHOD(TestingMarvelPoints)
		{
			World w(0, 5);
			w.run();
			Assert::IsTrue(w.m_gameOver);
			for (int i = 0; i < w.m_players.size(); i++)
			{
				Assert::AreEqual(w.m_players.at(i)->getMarvel()->getMarvelScore(),w.m_scores.at(i).at(WONDER_LEVEL));
			}
		}

		TEST_METHOD(GoldPoints)
		{
			World w(0, 5);
			w.run();
			Assert::IsTrue(w.m_gameOver);
			for (int i = 0; i < w.m_players.size(); i++)
			{
				Assert::AreEqual(w.m_players.at(i)->getMoney() / 3, (unsigned int) w.m_scores.at(i).at(GOLD));
			}
		}

		TEST_METHOD(BluePoints)
		{
			World w(0, 5);
			w.run();
			Assert::IsTrue(w.m_gameOver);
			for (int i = 0; i < w.m_players.size(); i++)
			{
				int bluePoints = 0;
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* c = w.m_players.at(i)->getBoard().at(j);
					if (c->m_color == BLUE)
					{
						bluePoints += c->getPoints();
					}
				}
				Assert::AreEqual(bluePoints, w.m_scores.at(i).at(BLUE_CARDS));
			}
		}

		TEST_METHOD(YellowPoints)
		{
			World w(0, 5);
			w.run();
			Assert::IsTrue(w.m_gameOver);
			for (int i = 0; i < w.m_players.size(); i++)
			{
				int value = 0;
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* c = w.m_players.at(i)->getBoard().at(j);
					if (c->m_color == YELLOW)
					{
						if (c->m_name == "PORT")
						{
							value += w.m_players.at(i)->countColor(BROWN);
						}
						if (c->m_name == "PHARE")
						{
							value += w.m_players.at(i)->countColor(YELLOW);
						}
						if (c->m_name == "CHAMBRE_DE_COMMERCE")
						{
							value += 2*w.m_players.at(i)->countColor(GRAY);
						}if (c->m_name == "ARENE")
						{
							value += w.m_players.at(i)->getMarvel()->getMarvelLevel();
						}
					}
				}
				int s = w.m_scores.at(i).at(YELLOW_CARDS);
				int t = w.m_players.at(i)->getGeneratedScore();
				Assert::AreEqual(value, w.m_scores.at(i).at(YELLOW_CARDS));
			}
		}

		//TOTEST
		/*
		3 GUILDE_DES_TRAVAILLEURS
		3 GUILDE_DES_ARTISANS
		3 GUILDE_DES_COMMERCANTS
		3 GUILDE_DES_PHILOSOPHES
		3 GUILDE_DES_ESPIONS
		3 GUILDE_DES_STRATEGES
		3 GUILDE_DES_ARMATEURS 
		3 GUILDE_DES_SCIENTIFIQUES
		3 GUILDE_DES_MAGISTRATS
		3 GUILDE_DES_BATISSEURS
		SCIENCE
		*/
	};
}