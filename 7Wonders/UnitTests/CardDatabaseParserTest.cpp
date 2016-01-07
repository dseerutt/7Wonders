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
			CardDatabaseParser parser2(4);
			CardSet set = parser2.generateDeck(0);
			Assert::AreEqual((size_t)21, set.size());
		}

		TEST_METHOD(CardDatabaseParserGenerateDeck7Players)
		{
			CardDatabaseParser parser(7);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)27, set.size());
		}

		TEST_METHOD(CardDatabaseParserGenerateDeck3Players)
		{
			CardDatabaseParser parser(2);
			CardSet set = parser.generateDeck(0);
			Assert::AreEqual((size_t)27, set.size());
		}
	};
}