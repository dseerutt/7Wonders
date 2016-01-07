#include "stdafx.h"
#include "CppUnitTest.h"
#include "../7Wonders/Card.h"
#include "../7Wonders/CardSet.cpp"
#include "../7Wonders/CardDatabaseParser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(CardDatabaseParserGenerateDeck4Players)
		{
			//m_brownCards m_blueCards m_yellowCards m_redCards m_greenCards
			//privés donc pas de test direct sur les contenus
			//Age 0 seulement testé

			//4 joueurs
			CardDatabaseParser parser(3);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)0, set.size());
			Assert::AreEqual((size_t)21, set.size());
		}

		TEST_METHOD(CardDatabaseParserGenerateDeck7Players)
		{
			CardDatabaseParser parser(8);
			CardSet set = parser.generateDeck(0);
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
			for (int i = 0; i < set.size(); i++)
			{
				std::vector<string>::iterator iter = contents.begin();
				while (iter != contents.end())
				{
					if (*iter == set[i]->m_name.c_str())
						iter = contents.erase(iter);
					else
						iter++;
				}
			}
			Assert::AreEqual((size_t) 0, contents.size());
		}

		TEST_METHOD(getColorTest)
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