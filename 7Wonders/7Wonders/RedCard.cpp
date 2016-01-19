#include "RedCard.h"

RedCard::RedCard(const std::string& name, unsigned int power, std::string cardName) : Card(name, RED, cardName), m_power(power)
{
}

RedCard::~RedCard()
{
}

unsigned int RedCard::getPoints() const
{
	return 0;
}

unsigned int RedCard::getPower() const
{
	return m_power;
}
