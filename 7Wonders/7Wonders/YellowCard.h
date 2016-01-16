#pragma once
#include "Card.h"

class YellowCard : public Card
{
private:
	const std::string m_production;
public:
	YellowCard(const std::string& name, const std::string& production);
	~YellowCard();

	virtual unsigned int getPoints() const;
	virtual unsigned int getPower() const;
	std::string getProduction() const;
};

