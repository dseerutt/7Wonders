#include "BrownCard.h"


BrownCard::BrownCard(const std::string& name, const std::string& production) : Card(name, BROWN), m_production(production)
{
}


BrownCard::~BrownCard()
{
}

unsigned int BrownCard::getPoints() const
{
	return 0;
}
