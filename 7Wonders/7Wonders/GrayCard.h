#pragma once
#include "Card.h"

class GrayCard :
	public Card
{
private:
	std::string m_production;
public:
	GrayCard(const std::string& name, const std::string& production);
	~GrayCard();

	virtual unsigned int getPoints() const;
};

