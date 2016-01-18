#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/BlueCard.h"
#include "../7Wonders/Player.h"
#include "../7Wonders/ComputerPlayer.h"
#include "../7Wonders/CardSet.h"
#include "../7Wonders/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PlayerTest)
	{
	public:
		
		TEST_METHOD(PlayerConstructor)
		{
			CardSet set;
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set, 6);
			Assert::IsTrue(cp.getBoard().empty());
			Assert::AreEqual((unsigned) 0, cp.getScore());
			Assert::AreEqual((unsigned)3, cp.getMoney());
			Assert::AreEqual((unsigned int) 0, cp.getGeneratedScore());
			Assert::IsTrue(cp.getBoard().empty());
			Assert::IsTrue(cp.getHand().empty());
			Assert::AreEqual(0, std::get<WOOD>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<STONE>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<BRICK>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<MINERAL>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<PAPYRUS>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<GLASS>(cp.getResources().at(0)));
			Assert::AreEqual(1, std::get<TEXTILE>(cp.getResources().at(0)));
			//pas de test de m_discard, m_cardToPlay car protected

		}

		TEST_METHOD(GetMoneyTest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			Assert::AreEqual((unsigned)3, cp.getMoney());
		}

		TEST_METHOD(CanBuyTest)
		{
			World w(2, 5);
			w.m_players.at(0)->resetResources();
			w.startAge();
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "CHANTIER")
				{
					index = i;
					break;
				}
			}
			Assert::IsTrue(w.m_players.at(0)->canBuy(w.m_deck.at(index)));
			
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "FRICHE")
				{
					index = i;
					break;
				}
			}
			Assert::IsTrue(w.m_players.at(0)->canBuy(w.m_deck.at(index)));

			w.m_deck.at(index)->m_price = 50;
			Assert::IsFalse(w.m_players.at(0)->canBuy(w.m_deck.at(index)));

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "PALISSADE")
				{
					index = i;
					break;
				}
			}

			Assert::IsFalse(w.m_players.at(0)->canBuy(w.m_deck.at(index)));


			std::array<int, RESOURCES_COUNT> nombre = { 0, 0, 0, 1, 0, 0, 1 };
			w.m_players.at(0)->AddResourceWithChoice(nombre);

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "CASERNE")
				{
					index = i;
					break;
				}
			}
			Assert::IsTrue(w.m_players.at(0)->canBuy(w.m_deck.at(index)));


		}

		TEST_METHOD(CanBuyWithNeighborSimpleTest)
		{
			//Cas de base
			World w(2, 5);
			w.startAge();
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "CHANTIER")
				{
					index = i;
					break;
				}
			}
			Assert::AreEqual(0, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "FRICHE")
				{
					index = i;
					break;
				}
			}

			Assert::AreEqual(0, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));
		}

		TEST_METHOD(CanBuyWithNeighborComplexTest)
		{
			//Cas des voisins
			World w(2, 5);
			w.m_players.at(0)->resetResources();
			w.m_players.at(0)->leftNeighbor->resetResources();
			w.m_players.at(0)->rightNeighbor->resetResources();
			w.startAge();
			CardSet Mycard;
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "PALISSADE")
				{
					index = i;
					break;
				}
			}
			Assert::AreEqual(-1, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));
			std::array<int, RESOURCES_COUNT> rec = { 1, 0, 0, 0, 0, 0, 0 };
			w.m_players.at(0)->leftNeighbor->AddResource(rec);
			Assert::AreEqual(2, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "SCRIPTORIUM")
				{
					index = i;
					break;
				}
			}

			Assert::AreEqual(-1, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));
			std::array<int, RESOURCES_COUNT> rec2 = { 0, 0, 0, 0, 1, 0, 0 };
			w.m_players.at(0)->rightNeighbor->AddResource(rec2);
			Assert::AreEqual(2, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));
		}


		TEST_METHOD(BuyWithNeighborSimpleTest)
		{
			//Cas de base
			World w(2, 5);
			Assert::AreEqual((unsigned)3, w.m_players.at(0)->getMoney());
			w.startAge();
			CardSet Mycard;
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "CHANTIER")
				{
					index = i;
					break;
				}
			}
			Assert::IsTrue(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			Assert::AreEqual((unsigned)3, w.m_players.at(0)->getMoney());
			

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "FRICHE")
				{
					index = i;
					break;
				}
			}

			Assert::IsTrue(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			Assert::AreEqual((unsigned)2, w.m_players.at(0)->getMoney());
		}

		TEST_METHOD(BuyWithNeighborComplexTest)
		{
			//Cas des voisins
			World w(2, 5);
			w.m_players.at(0)->resetResources();
			w.m_players.at(0)->leftNeighbor->resetResources();
			w.m_players.at(0)->rightNeighbor->resetResources();
			w.startAge();
			CardSet Mycard;
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "PALISSADE")
				{
					index = i;
					break;
				}
			}
			Assert::IsFalse(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			std::array<int, RESOURCES_COUNT> rec = { 1, 0, 0, 0, 0, 0, 0 };
			w.m_players.at(0)->leftNeighbor->AddResource(rec);
			Assert::IsTrue(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			Assert::AreEqual((unsigned)5, w.m_players.at(0)->leftNeighbor->getMoney());

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "SCRIPTORIUM")
				{
					index = i;
					break;
				}
			}

			Assert::IsFalse(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			std::array<int, RESOURCES_COUNT> rec2 = { 0, 0, 0, 0, 1, 0, 0 };
			w.m_players.at(0)->rightNeighbor->AddResource(rec2);
			Assert::IsTrue(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			Assert::AreEqual((unsigned)5, w.m_players.at(0)->rightNeighbor->getMoney());


			//Besoin des deux voisins
			//Besoin d'une fonction de fusion des resources
			/*
			Mycard.clear();
			BlueCard b("Ma carte", 5);
			b.m_price = 0;
			b.m_Cost[WOOD] = 1;
			b.m_Cost[STONE] = 0;
			b.m_Cost[BRICK] = 0;
			b.m_Cost[MINERAL] = 0;
			b.m_Cost[PAPYRUS] = 1;
			b.m_Cost[GLASS] = 0;
			b.m_Cost[TEXTILE] = 0;
			Mycard.push_back(&b);
			Assert::AreEqual(2, w.m_players.at(0)->canBuyWithNeighbor(Mycard));*/
		}

		TEST_METHOD(BuyWithNeighborComplexTest2)
		{
			//Cas des voisins
			World w(2, 5);
			w.m_players.at(0)->resetResources();
			w.m_players.at(0)->leftNeighbor->resetResources();
			w.m_players.at(0)->rightNeighbor->resetResources();
			w.startAge();
			int index = 0;

			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "SCRIPTORIUM")
				{
					index = i;
					break;
				}
			}

			std::array<int, RESOURCES_COUNT> rec2 = { 0, 0, 0, 0, 1, 0, 0 };
			w.m_players.at(0)->rightNeighbor->AddResource(rec2);

			Assert::IsTrue(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			Assert::AreEqual((unsigned)5, w.m_players.at(0)->rightNeighbor->getMoney());
		}

		TEST_METHOD(CanProvideTest)
		{
			CardSet c;
			ComputerPlayer cp(&c, 6);
			cp.resetResources();
			array<int, RESOURCES_COUNT> stock = { 1, 0, 0, 0, 0, 0, 0 };
			array<int, RESOURCES_COUNT> pb = { 1, 0, 0, 0, 0, 0, 1 };
			cp.AddResource(stock);
			Assert::IsTrue(cp.canProvide(stock));
			Assert::IsFalse(cp.canProvide(pb));
			array<int, RESOURCES_COUNT> choice = { 0, 0, 0, 0, 0, 1, 1 };
			cp.AddResourceWithChoice(choice);
			Assert::IsTrue(cp.canProvide(pb));
		}

		TEST_METHOD(CountResourcesTest)
		{
			CardSet c;
			ComputerPlayer cp(&c, 6);
			array<int, RESOURCES_COUNT> choice = { 0, 0, 0, 0, 0, 1, 2 };
			Assert::AreEqual(6, cp.countResourcesL(choice));
			array<int, RESOURCES_COUNT> choice2 = { 0, 0, 0, 0, 0, 0, 0 };
			Assert::AreEqual(0, cp.countResourcesL(choice2));
		}

		TEST_METHOD(GetScoreTest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			Assert::AreEqual((unsigned)0, cp.getScore());
		}

		TEST_METHOD(GetMilitaryTest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			Assert::AreEqual((unsigned)0, cp.getMilitary());
		}

		TEST_METHOD(GetBoardTest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			Assert::IsTrue(cp.getBoard().empty());
		}

		TEST_METHOD(SetHandTest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			Assert::IsTrue(cp.getHand().empty());

			CardSet set2;
			BlueCard card("carte bleue", 5, "-");
			set2.push_back(&card);
			cp.setHand(set2);
			Assert::IsTrue(!cp.getHand().empty());
			Assert::AreEqual(set2.at(0)->m_name, cp.getHand().at(0)->m_name);
		}

		TEST_METHOD(GetHandTest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			Assert::IsTrue(cp.getHand().empty());
			CardSet set2;
			BlueCard card("carte bleue", 5, "-");
			set2.push_back(&card);
			cp.setHand(set2);
			Assert::AreEqual(set2.at(0)->m_name, cp.getHand().at(0)->m_name);
		}

		TEST_METHOD(PrepareTurnETPlayTurnTest)
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
			Assert::AreEqual(7, (int)cp.getHand().size());
		}

		TEST_METHOD(playTurnTestBadCases1)
		{
			CardSet set;
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set, 6);
			CardSet hand;
			BlueCard card0("carte bleue0", 1, "-");
			BlueCard card1("carte bleue1", 2, "-");
			BlueCard card7("carte bleue7", 8, "-");
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
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set, 6);
			CardSet hand;
			BlueCard card0("carte bleue0", 1, "-");
			BlueCard card1("carte bleue1", 2, "-");
			BlueCard card7("carte bleue7", 8, "-");
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
			BlueCard card("carte bleue", 5, "-");
			set.push_back(&card);
			ComputerPlayer cp(&set, 6);
			CardSet hand;
			cp.setHand(hand);
			try {
				cp.prepareTurn();
			}
			catch (const char* & ex){
				Assert::AreEqual("Un joueur ne possède aucune carte en main", ex);
			}
		}

		TEST_METHOD(AddResourcetest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			std::array<int, RESOURCES_COUNT> nombre = { 0, 0, 0, 0, 2, 0, 0 };
			cp.AddResource(nombre);
			Assert::AreEqual(2, std::get<PAPYRUS>(cp.getResources().at(0)));

			std::array<int, RESOURCES_COUNT> nombre2 = { 1, 0, 0, 0, 1, 0, 0 };
			cp.AddResource(nombre2);
			Assert::AreEqual(3, std::get<PAPYRUS>(cp.getResources().at(0)));
			Assert::AreEqual(1, std::get<WOOD>(cp.getResources().at(0)));
		}

		TEST_METHOD(AddResourceAvecChoixtest)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			std::array<int, RESOURCES_COUNT> nombre = { 1, 0, 0, 0, 1, 0, 0 };
			cp.AddResourceWithChoice(nombre);
			Assert::AreEqual(1, std::get<WOOD>(cp.getResources().at(0)));
			Assert::AreEqual(1, std::get<PAPYRUS>(cp.getResources().at(1)));
			
			std::array<int, RESOURCES_COUNT> nombre2 = { 1, 0, 0, 0, 0, 0, 0 };
			cp.AddResource(nombre2);
			Assert::AreEqual(2, std::get<WOOD>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<PAPYRUS>(cp.getResources().at(0)));
			Assert::AreEqual(1, std::get<WOOD>(cp.getResources().at(1)));
			Assert::AreEqual(1, std::get<PAPYRUS>(cp.getResources().at(1)));
		}

		TEST_METHOD(AddResourceAvecChoixtest2)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			std::array<int, RESOURCES_COUNT> nombre2 = { 1, 0, 0, 0, 0, 0, 0 };
			cp.AddResource(nombre2);
			Assert::AreEqual(1, std::get<WOOD>(cp.getResources().at(0)));
			
			std::array<int, RESOURCES_COUNT> nombre = { 1, 0, 0, 0, 1, 0, 0 };
			cp.AddResourceWithChoice(nombre);
			Assert::AreEqual(2, std::get<WOOD>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<PAPYRUS>(cp.getResources().at(0)));
			Assert::AreEqual(1, std::get<WOOD>(cp.getResources().at(1)));
			Assert::AreEqual(1, cp.getResources().at(1).at(PAPYRUS));
		}

		TEST_METHOD(AddResourceAvecChoixtest3)
		{
			CardSet set;
			ComputerPlayer cp(&set, 6);
			cp.resetResources();
			std::array<int, RESOURCES_COUNT> nombre2 = { 1, 1, 0, 0, 0, 0, 0 };
			cp.AddResourceWithChoice(nombre2);

			std::array<int, RESOURCES_COUNT> nombre = { 0, 0, 0, 0, 1, 1, 1 };
			cp.AddResourceWithChoice(nombre);
			Assert::AreEqual(1, cp.getResources().at(0).at(WOOD));
			Assert::AreEqual(1, cp.getResources().at(0).at(PAPYRUS));
			Assert::AreEqual(1, cp.getResources().at(1).at(STONE));
			Assert::AreEqual(1, cp.getResources().at(1).at(PAPYRUS));
			Assert::AreEqual(1, cp.getResources().at(2).at(WOOD));
			Assert::AreEqual(1, cp.getResources().at(2).at(GLASS));
			Assert::AreEqual(1, cp.getResources().at(3).at(STONE));
			Assert::AreEqual(1, cp.getResources().at(3).at(GLASS));
			Assert::AreEqual(1, cp.getResources().at(4).at(WOOD));
			Assert::AreEqual(1, cp.getResources().at(4).at(TEXTILE));
			Assert::AreEqual(1, cp.getResources().at(5).at(STONE));
			Assert::AreEqual(1, cp.getResources().at(5).at(TEXTILE));
		}

		TEST_METHOD(IdentifyResourcetest)
		{
			Assert::AreEqual((int)WOOD, Player::identifyResource('b'));
			Assert::AreEqual((int)STONE, Player::identifyResource('p'));
			Assert::AreEqual((int)BRICK, Player::identifyResource('a'));
			Assert::AreEqual((int)MINERAL, Player::identifyResource('m'));
			Assert::AreEqual((int)PAPYRUS, Player::identifyResource('q'));
			Assert::AreEqual((int)GLASS, Player::identifyResource('v'));
			Assert::AreEqual((int)TEXTILE, Player::identifyResource('t'));
		}

			TEST_METHOD(ApplyEffectstestBrown)
		{
			World w(2, 5);
			w.startAge();
			w.m_players.at(0)->resetResources();
			int index = 0;
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "FRICHE")
				{
					index = i;
					break;
				}
			}
			w.m_players.at(0)->applyEffects(w.m_deck.at(index));
			Assert::AreEqual(1, w.m_players.at(0)->getResources().at(0).at(WOOD));
			Assert::AreEqual(1, w.m_players.at(0)->getResources().at(1).at(BRICK));
		}

			TEST_METHOD(ApplyEffectstestBrown2)
			{
				World w(2, 5);
				w.m_players.at(0)->resetResources();
				w.startAge();
				w.startAge();
				int index = 0;
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "SCIERIE")
					{
						index = i;
						break;
					}
				}
				w.m_players.at(0)->applyEffects(w.m_deck.at(index));
				Assert::AreEqual(2, w.m_players.at(0)->getResources().at(0).at(WOOD));
			}

			TEST_METHOD(ApplyEffectstestGray)
			{
				World w(2, 5);
				w.startAge();
				int index = 0;
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "METIER_A_TISSER")
					{
						index = i;
						break;
					}
				}
				w.m_players.at(0)->applyEffects(w.m_deck.at(index));
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(0).at(TEXTILE));
			}

			TEST_METHOD(ComptoirsTest)
			{
				World w(2, 5);
				w.m_players.at(0)->resetResources();
				w.m_players.at(0)->leftNeighbor->resetResources();
				w.m_players.at(0)->rightNeighbor->resetResources();
				w.startAge();
				std::array<int, RESOURCES_COUNT> nombre2 = { 1, 0, 0, 0, 0, 0, 0 };
				w.m_players.at(0)->leftNeighbor->AddResourceWithChoice(nombre2);
				int index = 0;
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "COMPTOIR_OUEST")
					{
						index = i;
						break;
					}
				}
				Assert::IsTrue(w.m_players.at(0)->canBuy(w.m_deck.at(index)));
				w.m_players.at(0)->Buy(w.m_deck.at(index));
				w.m_players.at(0)->applyEffects(w.m_deck.at(index));
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "PALISSADE")
					{
						index = i;
						break;
					}
				}
				w.m_players.at(0)->Buy(w.m_deck.at(index));
				Assert::AreEqual((unsigned)4, w.m_players.at(0)->leftNeighbor->getMoney());
				Assert::AreEqual((unsigned)2, w.m_players.at(0)->getMoney());
			}

			TEST_METHOD(ComptoirsTest2)
			{
				World w(2, 5);
				w.m_players.at(0)->resetResources();
				w.m_players.at(0)->leftNeighbor->resetResources();
				w.m_players.at(0)->rightNeighbor->resetResources();
				w.startAge();
				std::array<int, RESOURCES_COUNT> nombre2 = { 1, 0, 0, 0, 0, 0, 0 };
				w.m_players.at(0)->rightNeighbor->AddResourceWithChoice(nombre2);
				int index = 0;
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "COMPTOIR_EST")
					{
						index = i;
						break;
					}
				}
				Assert::IsTrue(w.m_players.at(0)->canBuy(w.m_deck.at(index)));
				w.m_players.at(0)->Buy(w.m_deck.at(index));
				w.m_players.at(0)->applyEffects(w.m_deck.at(index));
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "PALISSADE")
					{
						index = i;
						break;
					}
				}
				w.m_players.at(0)->Buy(w.m_deck.at(index));
				Assert::AreEqual((unsigned)4, w.m_players.at(0)->rightNeighbor->getMoney());
				Assert::AreEqual((unsigned)2, w.m_players.at(0)->getMoney());
			}

			TEST_METHOD(ComptoirsTest3)
			{
				World w(2, 5);
				w.m_players.at(0)->resetResources();
				w.m_players.at(0)->leftNeighbor->resetResources();
				w.m_players.at(0)->rightNeighbor->resetResources();
				w.startAge();
				std::array<int, RESOURCES_COUNT> nombre2 = { 0, 0, 0, 0, 0, 0, 1 };
				w.m_players.at(0)->rightNeighbor->AddResourceWithChoice(nombre2);
				int index = 0;
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "MARCHE")
					{
						index = i;
						break;
					}
				}
				Assert::IsTrue(w.m_players.at(0)->canBuy(w.m_deck.at(index)));
				w.m_players.at(0)->Buy(w.m_deck.at(index));
				w.m_players.at(0)->applyEffects(w.m_deck.at(index));
				for (int i = 0; i < w.m_deck.size(); i++)
				{
					string s = w.m_deck.at(i)->m_name;
					if (w.m_deck.at(i)->m_name == "OFFICINE")
					{
						index = i;
						break;
					}
				}
				w.m_players.at(0)->Buy(w.m_deck.at(index));
				Assert::AreEqual((unsigned)4, w.m_players.at(0)->rightNeighbor->getMoney());
				Assert::AreEqual((unsigned)2, w.m_players.at(0)->getMoney());
			}

			TEST_METHOD(AlreadyPlayedTest)
			{
				World w(0, 5);
				w.m_age++;
				w.m_deck = w.generateDeck(0);
				BlueCard b("Card 1", 5, "-");
				w.m_deck[0] = &b;
				w.distributeCards();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				Assert::IsFalse(w.m_players.at(0)->alreadyPlayed("Card 2"));
				Assert::IsTrue(w.m_players.at(0)->alreadyPlayed("Card 1"));
			}

			TEST_METHOD(ForumTest)
			{
				World w(0, 5);
				w.m_age++;
				w.m_deck = w.generateDeck(0);
				YellowCard b("Card 1", "f", "-");
				w.m_deck[0] = &b;
				w.distributeCards();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(0).at(PAPYRUS));
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(1).at(GLASS));
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(2).at(TEXTILE));
			}

			TEST_METHOD(CaravanserailTest)
			{
				World w(0, 5);
				w.m_players.at(0)->resetResources();
				w.m_age++;
				w.m_deck = w.generateDeck(0);
				YellowCard b("Card 1", "c", "-");
				w.m_deck[0] = &b;
				w.distributeCards();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(0).at(WOOD));
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(1).at(STONE));
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(2).at(BRICK));
				Assert::AreEqual(1, w.m_players.at(0)->getResources().at(3).at(MINERAL));
			}

			TEST_METHOD(TradeCountColorTest)
			{
				World w(0, 5);
				w.m_age++;
				w.m_deck = w.generateDeck(0);
				YellowCard b("Card 1", "c", "-");
				w.m_deck[0] = &b;
				w.distributeCards();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				int cpt = 1;
				if (w.m_players.at(0)->leftNeighbor->getBoard().at(0)->m_color == YELLOW)
				{
					cpt++;
				}
				if (w.m_players.at(0)->rightNeighbor->getBoard().at(0)->m_color == YELLOW)
				{
					cpt++;
				}
				int cpt2 = 0;
				if (w.m_players.at(0)->leftNeighbor->getBoard().at(0)->m_color == GRAY)
				{
					cpt2++;
				}
				if (w.m_players.at(0)->rightNeighbor->getBoard().at(0)->m_color == GRAY)
				{
					cpt2++;
				}
				Assert::AreEqual(cpt, w.m_players.at(0)->tradeCountColor(YELLOW));
				Assert::AreEqual(cpt2, w.m_players.at(0)->tradeCountColor(GRAY));
			}

			TEST_METHOD(CountColorTest)
			{
				World w(0, 5);
				w.startAge();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				w.play(*w.m_players.at(0));
				w.playOthers(*w.m_players.at(0));
				w.prepareTurn();
				w.playTurn();
				int cpt = 0;
				if (w.m_players.at(0)->getBoard().at(0)->m_color == BROWN)
				{
					cpt++;
				}
				if (w.m_players.at(0)->getBoard().at(1)->m_color == BROWN)
				{
					cpt++;
				}
				if (w.m_players.at(0)->getBoard().at(2)->m_color == BROWN)
				{
					cpt++;
				}
				Assert::AreEqual(cpt, w.m_players.at(0)->countColor(BROWN));
			}

			TEST_METHOD(UpgradeMarvelMoneyTest)
			{
				World w(0, 5);
				w.m_players.at(0)->upgradeMarvelMoney(4);
				Assert::AreEqual((unsigned int) 7, w.m_players.at(0)->getMoney());
			}

			TEST_METHOD(ResetResourceTest)
			{
				World w(0, 5);
				w.m_players.at(0)->resetResources();
				Assert::AreEqual((size_t) 1, w.m_players.at(0)->getResources().size());
				for (int i = 0; i < RESOURCES_COUNT; i++)
				{
					Assert::AreEqual(0, w.m_players.at(0)->getResources().at(0).at(i));
				}
			}
	};
}