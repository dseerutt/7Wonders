#include "YellowCard.h"

YellowCard::YellowCard(const std::string& name, const std::string& production) : Card(name, YELLOW), m_production(production)
{
}

YellowCard::~YellowCard()
{
}

unsigned int YellowCard::getPoints() const
{
	return 0;
}

unsigned int YellowCard::getPower() const
{
	return 0;
}

std::string YellowCard::getProduction() const
{
	return m_production;
}