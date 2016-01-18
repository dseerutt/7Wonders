#pragma once
#include "Card.h"
class BlueCard : public Card
{
private:
	unsigned int m_points;

public:
	BlueCard(const std::string& name, int points, std::string cardName);
	~BlueCard();

	virtual unsigned int getPoints() const;
	virtual unsigned int getPower() const;
};

