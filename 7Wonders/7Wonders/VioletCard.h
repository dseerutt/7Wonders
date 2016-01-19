#pragma once
#include "Card.h"

class VioletCard : public Card
{
public:
	VioletCard(const std::string& name, const std::string& production, std::string cardName);
	~VioletCard();

	virtual unsigned int getPoints() const;
	virtual unsigned int getPower() const;
	std::string getProduction() const;
};

