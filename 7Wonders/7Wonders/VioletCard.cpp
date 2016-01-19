#include "VioletCard.h"

VioletCard::VioletCard(const std::string& name, const std::string& production, std::string cardName) : Card(name, VIOLET, cardName)
{
	m_production = production;
}

VioletCard::~VioletCard()
{
}

unsigned int VioletCard::getPoints() const
{
	return 0;
}

unsigned int VioletCard::getPower() const
{
	return 0;
}

std::string VioletCard::getProduction() const
{
	return m_production;
}