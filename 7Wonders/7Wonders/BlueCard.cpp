#include "BlueCard.h"

BlueCard::BlueCard(const std::string& name, int points) : Card(name, BLUE), m_points(points)
{
}

BlueCard::~BlueCard()
{
}

unsigned int BlueCard::getPoints() const
{
	return m_points;
}

unsigned int BlueCard::getPower() const
{
	return 0;
}