#include "GrayCard.h"


GrayCard::GrayCard(const std::string& name, const std::string& production) : Card(name, GRAY), m_production(production)
{
}


GrayCard::~GrayCard()
{
}

unsigned int GrayCard::getPoints() const
{
	return 0;
}

string GrayCard::getProduction()
{
	return m_production;
}

unsigned int GrayCard::getPower() const
{
	return 0;
}