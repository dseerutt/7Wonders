#pragma once
#include <vector>
#include "Card.h"

#define DATABASE_PATH "../../cardsDatabase.txt"

class CardDatabaseParser
{
private:
	std::vector<std::vector<Card> > m_allCards;

public:
	CardDatabaseParser(int playerNumber);
	~CardDatabaseParser();

	std::vector<Card> generateDeck(int age);
	CardColor getColor(char c) const;
};

