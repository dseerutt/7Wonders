#include "RedCard.h"

RedCard::RedCard(const std::string& name, unsigned int power) : Card(name, RED), m_power(power)
{
}

RedCard::~RedCard()
{
}

unsigned int RedCard::getPoints() const
{
	return 0;
}

unsigned int RedCard::getPower()
{
	return m_power;
}
