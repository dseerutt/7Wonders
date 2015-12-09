#pragma once
#include "Card.h"

class BrownCard : public Card
{
private:
	std::string m_production;
public:
	BrownCard(const std::string& name, const std::string& production);
	~BrownCard();

	virtual unsigned int getPoints() const;
};

