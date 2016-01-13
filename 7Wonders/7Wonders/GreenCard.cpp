#include "GreenCard.h"

GreenCard::GreenCard(const std::string& name, char type) : Card(name, GREEN), m_type(type)
{
}

GreenCard::~GreenCard()
{
}

char GreenCard::getType() const
{
	return m_type;
}

unsigned int GreenCard::getPoints() const
{
	return 0;
}

unsigned int GreenCard::getPower() const
{
	return 0;
}
