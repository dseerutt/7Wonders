#pragma once
#include "Card.h"

class RedCard : public Card
{
private:
	unsigned int m_power;
public:
	RedCard(const std::string& name, unsigned int power);
	~RedCard();

	virtual unsigned int getPoints() const;
	unsigned int getPower() const;
};

