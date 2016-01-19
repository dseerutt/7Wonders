#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/CardSet.cpp"
#include "../7Wonders/CardDatabaseParser.cpp"
#include "../7Wonders/VioletCard.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CardDatabaseParserGenerateDeck3Players)
		{
			//m_brownCards m_blueCards m_yellowCards m_redCards m_greenCards
			//privés donc pas de test direct sur les contenus

			//3 joueurs
			CardDatabaseParser parser(3);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)21, set.size());
			set = parser.generateDeck(1);
			Assert::AreEqual((size_t)21, set.size());
			set = parser.generateDeck(2);
			//Assert::AreEqual((size_t)21, set.size());
		}

		TEST_METHOD(CardDatabaseParserGenerateDeck7Players)
		{
			CardDatabaseParser parser(8);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)49, set.size());
			set = parser.generateDeck(1);
			Assert::AreEqual((size_t)49, set.size());
			set = parser.generateDeck(2);
			Assert::AreEqual((size_t)49, set.size());
		}

		TEST_METHOD(CardDatabaseParserGenerateDeck2Players)
		{
			CardDatabaseParser parser(2);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)0, set.size());
			//pas de cartes pour 2 joueurs
		}

		TEST_METHOD(CardDatabaseParserTestContentsAge0)
		{
			//m_brownCards m_blueCards m_yellowCards m_redCards m_greenCards
			//privés donc pas de test direct sur les contenus
			//Age 0 seulement testé

			//4 joueurs
			CardDatabaseParser parser(3);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)21, set.size());
			vector<string> contents;
			contents.push_back("CHANTIER");
			contents.push_back("CAVITE");
			contents.push_back("BASSIN_ARGILEUX");
			contents.push_back("FILON");
			contents.push_back("FOSSE_ARGILEUSE");
			contents.push_back("EXPLOITATION_FORESTIERE");
			contents.push_back("METIER_A_TISSER");
			contents.push_back("VERRERIE");
			contents.push_back("PRESSE");
			contents.push_back("BAINS");
			contents.push_back("AUTEL");
			contents.push_back("THEATRE");
			contents.push_back("COMPTOIR_EST");
			contents.push_back("COMPTOIR_OUEST");
			contents.push_back("MARCHE");
			contents.push_back("PALISSADE");
			contents.push_back("CASERNE");
			contents.push_back("TOUR_DE_GARDE");
			contents.push_back("OFFICINE");
			contents.push_back("ATELIER");
			contents.push_back("SCRIPTORIUM");

			//Test du nombre d'éléments
			for (int i = 0; i < set.size(); i++)
			{
				std::vector<string>::iterator iter = contents.begin();
				while (iter != contents.end())
				{
					if (*iter == set[i]->m_name.c_str())
					{
						iter = contents.erase(iter);
					}
						
					else
						iter++;
				}
			}
			Assert::AreEqual((size_t) 0, contents.size());
		}

		TEST_METHOD(ParserCardCostTest)
		{
			World w(2, 3);
			w.generateDeck(0);
			for (int i = 0; i < w.m_deck.size(); i++)
			{
				if (w.m_deck.at(i)->m_name == "PALISSADE")
				{
					Assert::AreEqual(1, w.m_deck.at(i)->m_Cost[WOOD]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[STONE]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[BRICK]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[MINERAL]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[PAPYRUS]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[GLASS]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[TEXTILE]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_price);
				}

				if (w.m_deck.at(i)->m_name == "FRICHE")
				{
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[WOOD]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[STONE]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[BRICK]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[MINERAL]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[PAPYRUS]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[GLASS]);
					Assert::AreEqual(0, w.m_deck.at(i)->m_Cost[TEXTILE]);
					Assert::AreEqual(1, w.m_deck.at(i)->m_price);
				}
			}			
		}


		TEST_METHOD(GetColorTest)
		{
			CardDatabaseParser parser(3);
			Assert::AreEqual((int)BLUE, (int)parser.getColor('b'));
			Assert::AreEqual((int)GRAY, (int)parser.getColor('g'));
			Assert::AreEqual((int)BROWN, (int)parser.getColor('w'));
			Assert::AreEqual((int)GREEN, (int)parser.getColor('e'));
			Assert::AreEqual((int)YELLOW, (int) parser.getColor('y'));
			Assert::AreEqual((int)RED, (int) parser.getColor('r'));
		}
	};
}