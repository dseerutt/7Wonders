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
			BlueCard card("carte bleue", 5);
			set.push_back(&card);
			ComputerPlayer cp(&set);
			Assert::IsTrue(cp.getBoard().empty());
			Assert::AreEqual((unsigned) 0, cp.getScore());
			Assert::AreEqual((unsigned) 3, cp.getMoney());
			Assert::IsTrue(cp.getBoard().empty());
			Assert::IsTrue(cp.getHand().empty());
			Assert::AreEqual(0, std::get<WOOD>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<STONE>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<BRICK>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<MINERAL>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<PAPYRUS>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<GLASS>(cp.getResources().at(0)));
			Assert::AreEqual(0, std::get<TEXTILE>(cp.getResources().at(0)));
			//pas de test de m_discard, m_cardToPlay car protected

		}

		TEST_METHOD(GetMoneyTest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
			Assert::AreEqual((unsigned)3, cp.getMoney());
		}

		TEST_METHOD(CanBuyTest)
		{
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
			Assert::AreEqual(1, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));

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
			Assert::AreEqual(1, w.m_players.at(0)->canBuyWithNeighbor(w.m_deck.at(index)));

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
			Assert::IsFalse(w.m_players.at(0)->Buy(w.m_deck.at(index)));
			Assert::AreEqual((unsigned)3, w.m_players.at(0)->rightNeighbor->getMoney());


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
			ComputerPlayer cp(&c);
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
			array<int, RESOURCES_COUNT> choice = { 0, 0, 0, 0, 0, 1, 2 };
			Assert::AreEqual(3, Player::countResources(choice));
			array<int, RESOURCES_COUNT> choice2 = { 0, 0, 0, 0, 0, 0, 0 };
			Assert::AreEqual(0, Player::countResources(choice2));
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

		TEST_METHOD(AddResourcetest)
		{
			CardSet set;
			ComputerPlayer cp(&set);
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
			ComputerPlayer cp(&set);
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
			ComputerPlayer cp(&set);
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
			ComputerPlayer cp(&set);
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
	};
}