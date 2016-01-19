#include "BrownCard.h"


BrownCard::BrownCard(const std::string& name, const std::string& production, std::string cardName) : Card(name, BROWN, cardName), m_production(production)
{
}


BrownCard::~BrownCard()
{
}

unsigned int BrownCard::getPoints() const
{
	return 0;
}

string BrownCard::getProduction() const
{
	return m_production;
}

unsigned int BrownCard::getPower() const
{
	return 0;
}
