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
		TEST_METHOD(SciencePoints)
		{
			World w(0, 5);
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "GUILDE_DES_SCIENTIFIQUES")
				{
					index = i;
				}
			}
			BrownCard b("Carte_de_Substitution","b","-");

			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					w.updateMilitary();
					w.m_age++;
					if (w.m_age <= NUMBER_OF_AGES)
					{
						w.m_deck = w.generateDeck(w.m_age - 1);
						w.m_deck.at(index) = &b;
						w.distributeCards();
					}
				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}

			for (int i = 0; i < w.m_players.size(); i++)
			{
				unsigned int compass = 0, gear = 0, tablet = 0;
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					const GreenCard& card = (GreenCard&)(w.m_players.at(i)->getBoard().at(j));
					if (card.m_color == GREEN)
					{
						if (card.getType() == 'c')
							compass++;
						if (card.getType() == 'g')
							gear++;
						if (card.getType() == 't')
							tablet++;
					}
				}
				int res = compass*compass + gear*gear + tablet*tablet + 7 * std::min(compass, std::min(gear, tablet));
				Assert::AreEqual(res, w.m_scores.at(i).at(SCIENCE));
			}
		}

		TEST_METHOD(FreeCardTest)
		{
			World w(0, 5);
			int index = 0;
			BrownCard b("Carte_de_Substitution", "b", "CHANTIER");
			b.initCost(5, 5, 5, 5, 5, 5, 5, 5);

			w.m_age++;
			w.m_deck = w.generateDeck(w.m_age - 1);
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "CHANTIER")
				{
					index = i;
				}
			}
			w.m_deck.at(0) = w.m_deck.at(index);
			w.distributeCards();
			Player& p = *w.m_players[0];
			w.play(p);
			w.playOthers(p);
			w.endTurn();
			Assert::AreEqual("CHANTIER", w.m_players.at(0)->getBoard().at(0)->m_name.c_str());
			w.m_age++;
			w.m_deck = w.generateDeck(w.m_age - 1);
			w.m_deck.at(0) = &b;
			w.distributeCards();
			Assert::IsTrue(w.m_players.at(0)->canBuy(&b));
			w.play(p);
			w.playOthers(p);
			w.playTurn();
			Assert::AreEqual("Carte_de_Substitution", w.m_players.at(0)->getBoard().at(1)->m_name.c_str());
			Assert::IsTrue(w.m_players.at(0)->getMoney() >= 3);
		}

		TEST_METHOD(GuildeDesTravailleursTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_TRAVAILLEURS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_TRAVAILLEURS")
					{
						int res = w.m_players.at(i)->leftNeighbor->countColor(BROWN);
						res += w.m_players.at(i)->rightNeighbor->countColor(BROWN);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesArtisansTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_ARTISANS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_ARTISANS")
					{
						int res = w.m_players.at(i)->leftNeighbor->countColor(GRAY);
						res += w.m_players.at(i)->rightNeighbor->countColor(GRAY);
						Assert::AreEqual(2*res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesCommercantsTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_COMMERCANTS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_COMMERCANTS")
					{
						int res = w.m_players.at(i)->leftNeighbor->countColor(YELLOW);
						res += w.m_players.at(i)->rightNeighbor->countColor(YELLOW);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesPhilosophesTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_PHILOSOPHES")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_PHILOSOPHES")
					{
						int res = w.m_players.at(i)->leftNeighbor->countColor(GREEN);
						res += w.m_players.at(i)->rightNeighbor->countColor(GREEN);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesEspionsTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_ESPIONS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_ESPIONS")
					{
						int res = w.m_players.at(i)->leftNeighbor->countColor(RED);
						res += w.m_players.at(i)->rightNeighbor->countColor(RED);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesStrategesTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			unsigned int tab[7] = {};
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						for (int i = 0; i < w.m_players.size(); i++)
						{
							int value = w.m_players.at(i)->getMilitaryMalus();
							if (w.m_players.at(i)->getMilitary() < w.m_players.at(i)->leftNeighbor->getMilitary())
							{
								tab[i]++;
							}
							if (w.m_players.at(i)->getMilitary() < w.m_players.at(i)->rightNeighbor->getMilitary())
							{
								tab[i]++;
							}
							Assert::AreEqual(tab[i], w.m_players.at(i)->getMilitaryMalus());
						}
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_STRATEGES")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						for (int i = 0; i < w.m_players.size(); i++)
						{
								int value = w.m_players.at(i)->getMilitaryMalus();
								if (w.m_players.at(i)->getMilitary() < w.m_players.at(i)->leftNeighbor->getMilitary())
								{
									tab[i]++;
								}
								if (w.m_players.at(i)->getMilitary() < w.m_players.at(i)->rightNeighbor->getMilitary())
								{
									tab[i]++;
								}
								Assert::AreEqual(tab[i], w.m_players.at(i)->getMilitaryMalus());
						}
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();
			for (int i = 0; i < w.m_players.size(); i++)
			{
				int value = w.m_players.at(i)->getMilitaryMalus();
				if (w.m_players.at(i)->getMilitary() < w.m_players.at(i)->leftNeighbor->getMilitary())
				{
					tab[i]++;
				}
				if (w.m_players.at(i)->getMilitary() < w.m_players.at(i)->rightNeighbor->getMilitary())
				{
					tab[i]++;
				}
				Assert::AreEqual(tab[i], w.m_players.at(i)->getMilitaryMalus());
			}
			

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_STRATEGES")
					{
						Assert::AreEqual(tab[i], w.m_players.at(i)->getMilitaryMalus());
						int res = w.m_players.at(i)->leftNeighbor->getMilitaryMalus();
						res += w.m_players.at(i)->rightNeighbor->getMilitaryMalus();
						int res2 = w.m_scores.at(i).at(GUILDS);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesArmateursTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_ARMATEURS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_ARMATEURS")
					{
						int res = w.m_players.at(i)->countColor(BROWN);
						res += w.m_players.at(i)->countColor(GRAY) + w.m_players.at(i)->countColor(VIOLET);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesMagistratsTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_MAGISTRATS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_MAGISTRATS")
					{
						int res = w.m_players.at(i)->leftNeighbor->countColor(BLUE);
						res += w.m_players.at(i)->rightNeighbor->countColor(BLUE);
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesBatisseursTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_BATISSEURS")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();

			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_SCIENTIFIQUES")
					{
						int res = w.m_players.at(i)->leftNeighbor->getMarvel()->getMarvelLevel();
						res += w.m_players.at(i)->rightNeighbor->getMarvel()->getMarvelLevel() + w.m_players.at(i)->getMarvel()->getMarvelLevel();
						Assert::AreEqual(res, w.m_scores.at(i).at(GUILDS));
					}
				}
			}
		}

		TEST_METHOD(GuildeDesScientifiquesTest)
		{
			World w(0, 7);
			BrownCard b("Fake Card", "t", "-");
			b.initCost(0, 0, 0, 0, 0, 0, 0, 0);
			while (!w.m_gameOver)
			{
				if (w.betweenTurns())
				{
					if (w.m_age == 2)
					{
						w.updateMilitary();
						w.m_age++;
						if (w.m_age <= NUMBER_OF_AGES)
						{
							w.m_deck = w.generateDeck(w.m_age - 1);
							for (int i = 0; i < w.m_deck.size(); i++)
							{
								if (w.m_deck.at(i)->m_color == VIOLET)
								{
									Card* ccc = w.m_deck.at(i);
									if (w.m_deck.at(i)->m_name != "GUILDE_DES_SCIENTIFIQUES")
									{
										w.m_deck.at(i) = &b;
									}
								}
							}
							w.distributeCards();
						}
					}
					else {
						w.updateMilitary();
						w.startAge();
					}

				}
				Player& p = *w.m_players[0];
				w.play(p);
				w.playOthers(p);
				w.endTurn();
			}
			w.computeScores();
			int index = 0, c = 0, g = 0, t = 0;
			for (int i = 0; i < w.m_players.size(); i++)
			{
				for (int j = 0; j < w.m_players.at(i)->getBoard().size(); j++)
				{
					Card* ccc = w.m_players.at(i)->getBoard().at(j);
					if (w.m_players.at(i)->getBoard().at(j)->m_name == "GUILDE_DES_SCIENTIFIQUES")
					{
						Assert::AreEqual(0, w.m_scores.at(i).at(GUILDS));
						index = i;
					}
				}
			}
			for (int j = 0; j < w.m_players.at(index)->getBoard().size(); j++)
			{
				if (w.m_players.at(index)->getBoard().at(j)->m_color == GREEN)
				{
					switch (((GreenCard*) w.m_players.at(index)->getBoard().at(j))->getType())
					{
					case 'c':
						c++;
						break;
					case 'g':
						g++;
						break;
					case 't':
						t++;
						break;
					default:
						break;
					}
				}
			}
			int value = c*c + g*g + t*t + 7 * std::min(c, std::min(g, t));
			c++;
			int v1 = c*c + g*g + t*t + 7 * std::min(c, std::min(g, t));
			c--;
			g++;
			int v2 = c*c + g*g + t*t + 7 * std::min(c, std::min(g, t));
			g--;
			t++;
			int v3 = c*c + g*g + t*t + 7 * std::min(c, std::min(g, t));
			t--;
			int newValue = std::max(std::max(v1, v2), v3);
			Assert::AreEqual(newValue, w.m_scores.at(index).at(SCIENCE));
		}
		//TOTEST
		/*
		Armateurs
		//faire merveille avec voisin
		//acheter resource partagée
		//Gold Check
		*/
	};
}