#pragma once
#include "Card.h"

class YellowCard : public Card
{
private:

public:
	YellowCard(const std::string& name);
	~YellowCard();

	virtual unsigned int getPoints() const;
};

