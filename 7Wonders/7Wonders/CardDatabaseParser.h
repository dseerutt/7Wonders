#pragma once
#include <vector>
#include "CardSet.h"
#include "BrownCard.h"
#include "GrayCard.h"
#include "BlueCard.h"
#include "YellowCard.h"
#include "RedCard.h"
#include "GreenCard.h"
#include "VioletCard.h"

#define DATABASE_PATH "../../cardsDatabase.txt"

class CardDatabaseParser
{
private:
	std::vector<std::vector<BrownCard> > m_brownCards;
	std::vector<std::vector<GrayCard> > m_grayCards;
	std::vector<std::vector<BlueCard> > m_blueCards;
	std::vector<std::vector<YellowCard> > m_yellowCards;
	std::vector<std::vector<RedCard> > m_redCards;
	std::vector<std::vector<GreenCard> > m_greenCards;
	std::vector<std::vector<VioletCard> > m_violetCards;

public:
	CardDatabaseParser(int playerNumber, int numberOfAge);
	~CardDatabaseParser();

	CardSet generateDeck(int age);
	CardColor getColor(char c) const;
};

