#include "YellowCard.h"

YellowCard::YellowCard(const std::string& name) : Card(name, YELLOW)
{
}

YellowCard::~YellowCard()
{
}

unsigned int YellowCard::getPoints() const
{
	return 0;
}