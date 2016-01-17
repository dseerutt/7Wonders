#pragma once
#include "Card.h"

class YellowCard : public Card
{
public:
	YellowCard(const std::string& name, const std::string& production);
	~YellowCard();

	virtual unsigned int getPoints() const;
	virtual unsigned int getPower() const;
	std::string getProduction() const;
};

